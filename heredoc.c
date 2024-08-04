/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:17:00 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:37:24 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_init(t_mini *mini)
{
	int	i;

	i = 0;
	if (stack_heredocs(mini) == false)
		return (free_doc(mini->heredocs), false);
	while (mini->heredocs[i] != NULL)
	{
		mini->heredocs[i]->bytes = 0;
		mini->heredocs[i]->name = heredoc_name_gen(mini);
		if (mini->heredocs[i]->name == NULL)
			return (free_doc(mini->heredocs), false);
		mini->heredocs[i]->fd = open(mini->heredocs[i]->name, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (mini->heredocs[i]->fd == -1)
		{
			ft_exit(mini, strerror(errno), errno, 0);
			return (free_doc(mini->heredocs), false);
		}
		i++;
	}
	return (true);
}

int	grab_line(t_mini *mini, t_doc *doc)
{
	char	*input;

	input = readline("> ");
	if (input == NULL)
	{
		mini->hd_count--;
		return (ft_free(input), 1);
	}
	if (g_sig != 0)
	{
		mini->heredoc = false;
		return (unlink(doc->name), ft_free(input), close(doc->fd), 1);
	}
	if (ft_strchr(input, '$') != NULL && mini->qflag == 0)
		input = expand_string(mini, input);
	if (ft_strcmp(doc->delim, input) == 0)
		return (close(doc->fd), ft_free(input), 1);
	if (write(doc->fd, input, ft_strlen(input)) == -1)
		return (ft_free(input), 1);
	if (write(doc->fd, "\n", 1) == -1 && g_sig == 0)
		return (ft_free(input), 1);
	if (ft_strcmp(input, "") == 0)
		return (0);
	else
		return (ft_free(input), 0);
}

void	exe_tool(t_mini *mini, t_doc *doc)
{
	close(doc->fd);
	doc->pid = heredoc_child(mini);
	if (doc->pid == 0)
	{
		if (is_builtin(mini) == false && mini->path != NULL)
		{
			if (execve(mini->path, mini->args, mini->env) == -1)
				ft_exit(mini, "command not found", errno, 0);
		}
		close_fds();
		exit(mini->errno_code);
	}
	else
	{
		if (is_builtin(mini) == true)
			alias(mini);
		waitpid(doc->pid, &mini->status, 0);
		if (WIFEXITED(mini->errno_code))
			mini->errno_code = WEXITSTATUS(mini->errno_code);
		else if (WIFSIGNALED(mini->errno_code))
			mini->errno_code = WTERMSIG(mini->errno_code) + 128;
		return ;
	}
}

int	exe_heredoc(t_mini *mini, t_doc *doc)
{
	int	outfile_fd;

	close(doc->fd);
	doc->fd = open(doc->name, O_RDONLY);
	if (doc->fd == -1)
		ft_exit(mini, strerror(errno), errno, 0);
	if (mini->cmds[mini->i + 1] == NULL)
		dup2(doc->fd, STDIN_FILENO);
	else
		dup2(doc->fd, mini->fd[mini->i][1]);
	if (mini->outfile != NULL)
	{
		outfile_fd = open(mini->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			return (ft_exit(mini, strerror(errno), errno, 0), false);
		dup2(outfile_fd, STDOUT_FILENO);
	}
	if (mini->errno_code == 0)
		exe_tool(mini, doc);
	else
		(ft_exit(mini, "command not found", 127, 0), close(doc->fd));
	if (mini->outfile != NULL)
		close(outfile_fd);
	return (true);
}

int	heredoc(t_mini *mini)
{
	if (g_sig == SIGINT || g_sig == SIGQUIT)
	{
		sig_reset(mini, g_sig);
		mini->hd_count = 0;
		if (g_sig == SIGINT)
			return (free_doc(mini->heredocs), rl_replace_line("", 0), true);
	}
	if (pre_run(mini) == false)
		return (free_doc(mini->heredocs), true);
	while (1)
	{
		if (grab_line(mini, mini->heredocs[mini->hd_i]) == 1)
		{
			mini->qflag = 0;
			if (g_sig != 0)
			{
				return (free_doc(mini->heredocs), true);
			}
			else
				break ;
		}
	}
	if (heredoc_tool(mini, mini->hd_i) == false)
		return (free_doc(mini->heredocs), false);
	return (free_doc(mini->heredocs), true);
}
