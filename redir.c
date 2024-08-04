/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:05:44 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 15:10:22 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_util1(t_mini *mini, int i)
{
	if ((mini->outfile[0] == '/' && ft_getenv(mini, mini->outfile) != NULL))
	{
		ft_exit(mini, "Is a directory", 1, 0);
		return (false);
	}
	if (access(mini->outfile, R_OK) == -1)
		return (ft_exit(mini, "Permission denied", 1, 0), false);
	if (ft_strncmp(mini->args[i], ">>", 2) == 0)
	{
		if (redir_append(mini) == false)
			return (false);
	}
	else
		if (redir_out(mini) == false)
			return (false);
	return (true);
}

int	redir_util2(t_mini *mini, int i)
{
	if (mini->infile != NULL)
		free(mini->infile);
	mini->infile = ft_strdup(mini->args[i + 1]);
	if (mini->infile == NULL)
	{
		ft_exit(mini, "Bad infile", 2, 0);
		return (false);
	}
	if (access(mini->infile, F_OK) == -1)
	{
		if (mini->i == mini->count - 1)
		{
			ft_exit(mini, "No such file or directory", 2, 0);
			return (false);
		}
	}
	return (true);
}

void	redir_loop(t_mini *mini)
{
	int	i;

	i = -1;
	while (mini->args[++i] != NULL)
	{
		if (ft_strcmp(mini->args[i], ">") == 0 || \
			ft_strcmp(mini->args[i], "<<") == 0 || \
			ft_strcmp(mini->args[i], ">>") == 0 || \
			ft_strcmp(mini->args[i], "<") == 0)
		{
			free(mini->args[i]);
			mini->args[i] = " ";
			if (mini->args[i + 1] != NULL && mini->args[i + 1][0] != '\0')
				(free(mini->args[i + 1]), mini->args[i + 1] = " ");
			i++;
		}
	}
	i = -1;
	while (mini->args[++i] != NULL)
		arg_shuffle(mini->args);
	mini->hd_i = 0;
	if (mini->args[0] != NULL && mini->outfile != NULL \
		&& path_tool(mini) == true && mini->heredoc == false)
		dup2(mini->fd[mini->i][1], STDOUT_FILENO);
}

static int	out_check(t_mini *mini, char *arg)
{
	if (dir_check(mini, arg) == false)
		return (ft_exit(mini, "Is a directory", 1, 0), false);
	if (access(arg, F_OK) == -1)
		return (false);
	if (access(arg, W_OK) == -1)
		return (ft_exit(mini, "Permission denied", 1, 0), false);
	if (mini->outfile != NULL)
		free(mini->outfile);
	return (true);
}

int	find_outfile(t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->args[i] != NULL)
		i++;
	i--;
	while (i >= 0)
	{
		if (mini->args[i] && (ft_strcmp(mini->args[i], ">") == 0 || \
			ft_strcmp(mini->args[i], ">>") == 0))
		{
			if (out_check(mini, mini->args[i + 1]) == false)
				return (false);
			temp = ft_strdup(mini->args[i + 1]);
			if (temp == NULL)
				return (false);
			mini->outfile = remove_quotes(mini, temp);
			if (mini->outfile == NULL)
				return (false);
			return (true);
		}
		i--;
	}
	return (true);
}
