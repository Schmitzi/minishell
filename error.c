/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:55:18 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/06 11:21:37 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_mini *mini, char *str, int errno_code, int fd)
{
	if (fd == 0)
		fd = 2;
	else
	{
		if (mini->fd && mini->i < mini->count && mini->fd[mini->i] != NULL
			&& mini->cmds[mini->i + 1] != NULL)
			fd = mini->fd[mini->i][1];
	}
	mini->errno_code = errno_code;
	if (str != NULL)
	{
		write(fd, "minishell: ", 11);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

void	clear_garbage(t_mini *mini)
{
	if (mini->cmds && mini->i == mini->count)
		free_array(mini->cmds);
	free_array(mini->path_entries);
	free_pipes(mini);
}

void	move_to_end_and_free(char **array, int i)
{
	free(array[i]);
	array[i] = NULL;
	while (array[i + 1])
	{
		array[i] = array[i + 1];
		i++;
	}
	array[i] = NULL;
}

void	ft_unset(t_mini *mini)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (mini->args[++i] != NULL && mini->count == 1)
	{
		j = 0;
		while (mini->env[j] != NULL)
		{
			len = ft_strlen(mini->args[i]);
			if (ft_strncmp(mini->args[i], mini->env[j], len) == 0 && \
				ft_strcmp(mini->args[i], "_") != 0)
			{
				if (ft_strcmp(mini->args[i], "PATH") == 0 || \
					ft_strcmp(mini->args[i], "PWD") == 0 || \
					ft_strcmp(mini->args[i], "OLDPWD") == 0)
					edit_env(mini, mini->args[i], "");
				else
					move_to_end_and_free(mini->env, j);
				break ;
			}
			j++;
		}
	}
}

int	arg_checker(t_mini *mini)
{
	if (mini->args[0] == NULL)
		return (false);
	if (ft_strcmp(mini->args[0], ".") == 0)
		return (false);
	if (is_builtin(mini) == true)
		mini->errno_code = 0;
	if (open(mini->args[0], O_RDONLY) != -1 || \
		access(mini->args[0], X_OK) != 0 || \
		access_check(mini, mini->args[0]) == true)
		return (true);
	return (false);
}
