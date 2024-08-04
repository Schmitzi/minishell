/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:55:31 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 18:19:19 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_entries(t_mini *mini)
{
	char	*path;

	if (mini->path != NULL)
	{
		free(mini->path);
		mini->path = NULL;
	}
	path = ft_getenv(mini, "PATH");
	if (path == NULL)
	{
		ft_exit(mini, "Environment variable PATH not found", errno, 0);
		return (false);
	}
	mini->path_entries = ft_split(path, ':');
	if (mini->path_entries == NULL)
	{
		ft_exit(mini, "Memory allocation for path_entries failed", errno, 0);
		return (false);
	}
	return (true);
}

static int	path_loop(t_mini *mini, char *dir)
{
	if (mini->path != NULL)
		free(mini->path);
	mini->path = ft_strdup(dir);
	if (mini->path == NULL)
		return (free(dir), false);
	return (free(dir), true);
}

int	path_tool(t_mini *mini)
{
	char	*dir;
	char	*temp;
	size_t	i;

	i = 0;
	while (mini->path_entries[i] != NULL)
	{
		temp = ft_strjoin(mini->path_entries[i], "/");
		if (temp == NULL)
			return (false);
		dir = ft_strjoin(temp, mini->args[0]);
		if (dir == NULL)
			return (free(temp), false);
		free(temp);
		if (access(dir, X_OK) != -1)
			return (path_loop(mini, dir));
		free(dir);
		i++;
	}
	if (mini->heredoc == true)
		return (mini->errno_code = 127, false);
	if (is_builtin(mini) == false)
		return (ft_exit(mini, "command not found", 127, 0), false);
	return (true);
}

int	find_path(t_mini *mini)
{
	size_t	i;

	i = 0;
	if (mini->args == NULL)
		ft_exit(mini, "bad mini->args", errno, 0);
	if (access(mini->args[i], X_OK) != -1)
	{
		mini->path = ft_strdup(mini->args[i]);
		if (mini->path == NULL)
			return (ft_exit(mini, "path access", errno, 0), false);
	}
	else
	{
		if (ft_strncmp(mini->args[0], "./", 2) == 0 || \
		ft_strncmp(mini->args[0], "/", 1) == 0)
		{
			if (access(mini->args[0], X_OK) == -1)
				return (ft_exit(mini, "Permission denied", 126, \
				0), false);
			return (true);
		}
		if (path_tool(mini) == false && mini->heredoc == false)
			return (free(mini->path), false);
	}
	return (true);
}

char	*input_builder(t_mini *mini)
{
	char	*input;
	char	*temp;

	input = ft_strjoin(GREEN, mini->cwd);
	if (input == NULL)
	{
		free(mini->cwd);
		mini->cwd = ft_getenv(mini, "HOME");
		edit_env(mini, "PWD", mini->cwd);
		input = ft_strjoin(GREEN, mini->cwd);
	}
	temp = ft_strjoin(input, ": ");
	if (temp == NULL)
	{
		ft_exit(mini, "Memory allocation for temp failed", errno, 0);
		return (free(input), NULL);
	}
	free(input);
	input = ft_strjoin(temp, RESET);
	if (input == NULL)
		return (free(temp), NULL);
	free(temp);
	return (input);
}
