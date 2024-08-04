/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:44:30 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 13:26:53 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_setter(t_mini *mini)
{
	struct stat	path_stat;

	if (stat(mini->args[0], &path_stat) == -1)
	{
		ft_exit(mini, "No such file or directory,", 127, 0);
		return (false);
	}
	if (S_ISDIR(path_stat.st_mode) && mini->heredoc == false)
	{
		ft_exit(mini, "Is a directory", 126, 0);
		return (false);
	}
	if (access(mini->args[0], F_OK) == 0)
	{
		if (find_path(mini) == false)
			return (false);
		return (true);
	}
	if (access(post_trim(mini->args[0], '/'), F_OK) == -1)
	{
		ft_exit(mini, "No such file or directoryn", 127, 0);
		return (false);
	}
	return (true);
}

int	no_path(t_mini *mini)
{
	char	*path;

	path = ft_getenv(mini, "PATH");
	if (path == NULL && mini->args[0][0] != '/')
	{
		ft_exit(mini, "No such file or directorym", 127, 0);
		return (free(path), false);
	}
	else
	{
		if (find_path(mini) == false)
			return (false);
		if (mini->path == NULL && mini->heredoc == false && \
			mini->args[0][0] != '<' && mini->args[0][0] != '>')
		{
			if (mini->i < mini->count - 1)
				close(mini->fd[mini->i][1]);
			if (mini->i > 0)
				close(mini->fd[mini->i - 1][0]);
			dup2(mini->orig_stdin, STDIN_FILENO);
			dup2(mini->orig_stdout, STDOUT_FILENO);
			return (ft_exit(mini, "command not found", 127, 0), false);
		}
	}
	return (true);
}

int	pathfinder(t_mini *mini)
{
	if (mini->args[0] == NULL)
		return (ft_exit(mini, NULL, 0, 0), false);
	if (ft_strncmp(mini->args[0], "./", 2) == 0 || \
		mini->args[0][0] == '/')
	{
		if (access(mini->args[0], F_OK) != -1)
		{
			if (path_setter(mini) == false)
				return (false);
		}
		else
		{
			mini->path = ft_strdup(mini->args[0]);
			if (mini->path == NULL)
				return (false);
		}
		block_sig();
	}
	else if (is_builtin(mini) == false)
		if (no_path(mini) == false)
			return (false);
	return (true);
}

int	skip_space(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

void	ft_freemain(t_mini *mini)
{
	if (mini->input)
		free(mini->input);
	if (mini->path)
		free(mini->path);
	free(mini->oldpwd);
	free(mini->cwd);
	if (getenv("TERM") != NULL)
		free_array(mini->env);
	if (mini->infile)
		free(mini->infile);
	if (mini->outfile)
		free(mini->outfile);
	if (mini->curr_pid != NULL)
		free(mini->curr_pid);
	close_fds();
	if (g_sig == 0)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}
