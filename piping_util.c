/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:27:00 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 14:09:15 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_fds(t_mini *mini)
{
	if (mini->i > 0)
	{
		close(mini->fd[mini->i - 1][1]);
		if (!mini->infile)
			dup2(mini->fd[mini->i - 1][0], STDIN_FILENO);
		close(mini->fd[mini->i - 1][0]);
	}
	if (mini->i < mini->count - 1)
	{
		close(mini->fd[mini->i][0]);
		dup2(mini->fd[mini->i][1], STDOUT_FILENO);
		close(mini->fd[mini->i][1]);
	}
	close_fds();
}

static void	parent_stop(t_mini *mini)
{
	dup2(mini->orig_stdout, STDOUT_FILENO);
	dup2(mini->orig_stdin, STDIN_FILENO);
	if (mini->args[0] && ft_strcmp(mini->args[0], "exit") == 0)
	{
		waitpid(mini->pid[mini->i], &mini->status, 0);
		return ;
	}
	waitpid(mini->pid[mini->i], &mini->errno_code, 0);
	if (WIFEXITED(mini->errno_code))
		mini->errno_code = WEXITSTATUS(mini->errno_code);
	else if (WIFSIGNALED(mini->errno_code))
		mini->errno_code = WTERMSIG(mini->errno_code) + 128;
}

void	parent_fds(t_mini *mini)
{
	if (mini->redir)
	{
		dup2(mini->orig_stdout, STDOUT_FILENO);
		dup2(mini->orig_stdin, STDIN_FILENO);
	}
	if (mini->i < mini->count - 1)
	{
		close(mini->fd[mini->i][1]);
	}
	if (mini->i > 0)
	{
		close(mini->fd[mini->i - 1][0]);
		close(mini->fd[mini->i - 1][1]);
	}
	if (mini->i == mini->count - 1)
		parent_stop(mini);
	mini->redir = false;
}

void	arg_count(t_mini *mini)
{
	int	i;
	int	isq;
	int	idq;

	i = 0;
	isq = 0;
	idq = 0;
	mini->count = 1;
	while (mini->input[i] != '\0')
	{
		if (mini->input[i] == '\"' && !isq)
			idq = !idq;
		if (mini->input[i] == '\'' && !idq)
			isq = !isq;
		if (mini->input[i] == '|' && !isq && !idq)
			mini->count++;
		i++;
	}
}

int	cmd_check(t_mini *mini)
{
	if (mini->args == NULL || mini->args[0] == NULL || \
	(mini->args[0][0] == '.' && mini->args[0][1] != '/'))
	{
		if (mini->heredoc == true || mini->infile != NULL \
			|| mini->outfile != NULL)
			return (true);
		return (true);
	}
	if ((mini->args[0][0] == '~' && mini->args[0][1] == '\0') || \
		(mini->args[0][0] == '/' && mini->args[0][1] == '\0'))
	{
		ft_exit(mini, "Is a directory", 126, 0);
		return (false);
	}
	return (true);
}
