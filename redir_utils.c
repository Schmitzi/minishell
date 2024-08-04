/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:04:32 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 14:56:29 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_append(t_mini *mini)
{
	if (mini->outfile != NULL)
	{
		mini->fd[mini->i][1] = open(mini->outfile, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (access(mini->outfile, F_OK) == -1)
		{
			ft_exit(mini, "Permission denied", 1, 0);
			return (false);
		}
		mini->redir = true;
	}
	return (true);
}

int	redir_out(t_mini *mini)
{
	if (mini->outfile != NULL)
	{
		mini->fd[mini->i][1] = open(mini->outfile, O_WRONLY | \
			O_CREAT | O_TRUNC, 0644);
		if (access(mini->outfile, F_OK) == -1)
		{
			ft_exit(mini, "Permission denied", 1, 0);
			return (false);
		}
		mini->redir = true;
	}
	return (true);
}

int	redir_in(t_mini *mini)
{
	int	in_fd;

	if (mini->infile != NULL)
	{
		in_fd = open(mini->infile, O_RDONLY);
		if (in_fd == -1)
		{
			ft_exit(mini, "Permission denied", 1, 0);
			return (false);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		mini->redir = true;
	}
	return (true);
}

int	redir_count(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i] != NULL)
	{
		if (ft_strcmp(mini->args[i], "<<") == 0)
			mini->heredoc = true;
		if (!ft_strcmp(mini->args[i], ">>") || !ft_strcmp(mini->args[i], ">"))
		{
			if (ft_strcmp(mini->args[i + 1], "") == 0)
				return (ft_exit(mini, "ambiguous redirect", 1, 0), false);
			open(mini->args[i + 1], O_WRONLY | O_CREAT, 0644);
			if (access(mini->args[i + 1], W_OK | R_OK) == -1)
				return (false);
			i++;
		}
		else if (mini->args[i][0] == '<' && mini->args[i][1] == '\0')
		{
			if (in_check(mini, mini->args[i + 1]) == false)
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}

int	in_check(t_mini *mini, char *arg)
{
	if (access(arg, F_OK) == -1)
	{
		if (mini->errno_code == 0)
			ft_exit(mini, "No such file or directory", 1, 0);
		else
			ft_exit(mini, NULL, 1, 0);
		if (mini->infile != NULL)
			free(mini->infile);
		return (false);
	}
	if (access(arg, R_OK) == -1)
	{
		ft_exit(mini, "Permission denied", 1, 0);
		if (mini->infile != NULL)
			free(mini->infile);
		return (false);
	}
	return (true);
}
