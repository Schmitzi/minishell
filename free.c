/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:46:42 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 18:24:48 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_mini(t_mini *mini)
{
	if (mini->args)
		free_array(mini->args);
	if (mini->cmds)
		free_array(mini->cmds);
	(free_array(mini->env), free(mini->oldpwd));
	mini->oldpwd = NULL;
	free_array(mini->path_entries);
	free(mini->cwd);
	mini->cwd = NULL;
	free(mini->input);
	mini->input = NULL;
	if (mini->path)
		free(mini->path);
	if (mini->infile)
		free(mini->infile);
	if (mini->outfile)
		free(mini->outfile);
	if (mini->curr_pid)
		free(mini->curr_pid);
	(free_pipes(mini), close_fds());
	if (g_sig == 0)
	{
		(close(STDIN_FILENO), close(STDOUT_FILENO));
		close(STDERR_FILENO);
	}
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] && array[i] != NULL)
	{
		if (array[i] != NULL && ft_strcmp(array[i], "") != 0)
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
	if (array != NULL)
		free(array);
}

void	free_pipes(t_mini *mini)
{
	int	i;

	if (mini->fd != NULL)
	{
		i = 0;
		while (i <= mini->count - 1)
		{
			if (mini->fd[i])
			{
				close(mini->fd[i][0]);
				close(mini->fd[i][1]);
				free(mini->fd[i]);
			}
			i++;
		}
		free(mini->fd[i]);
		free(mini->fd);
	}
	if (mini->pid != NULL)
	{
		free(mini->pid);
		mini->pid = NULL;
	}
}

void	free_doc(t_doc **doc)
{
	int	i;

	i = 0;
	if (doc == NULL)
		return ;
	while (doc[i] != NULL)
	{
		if (doc[i]->fd != -1)
			close(doc[i]->fd);
		if (doc[i]->bytes != 0)
			free(doc[i]->line);
		if (doc[i]->delim != NULL && ft_strcmp(doc[i]->delim, "") != 0)
			free(doc[i]->delim);
		unlink(doc[i]->name);
		if (doc[i]->name != NULL)
			free(doc[i]->name);
		free(doc[i]);
		i++;
	}
	free(doc);
}

void	free_parent(t_mini *mini)
{
	if (mini->path_entries != NULL)
		free_array(mini->path_entries);
	if (mini->args != NULL)
		free_array(mini->args);
	if (mini->outfile != NULL)
	{
		free(mini->outfile);
		mini->outfile = NULL;
	}
	if (mini->infile != NULL)
	{
		free(mini->infile);
		mini->infile = NULL;
	}
}
