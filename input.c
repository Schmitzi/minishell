/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:00:23 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:32:03 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_util(t_mini *mini, char **cmds, int i)
{
	char	*dir;
	char	*arg;
	int		j;

	j = 0;
	while (mini->path_entries[j])
	{
		if (cmds[i][0] == '$' && !builtin_check(cmds[i]))
			return (true);
		arg = str_cleaner(cmds[i], i);
		if (arg == NULL)
			return (false);
		if (ft_strcmp(arg, "") == 0)
			return (free(arg), false);
		dir = ft_strjoin(mini->path_entries[j], "/");
		if (dir == NULL)
			return (free(arg), false);
		dir = ft_strjoin(dir, arg);
		if (dir == NULL)
			return (free(arg), false);
		if (access(dir, X_OK) != -1)
			return (free(dir), free(arg), true);
		j++;
	}
	return (false);
}

int	dir_check(t_mini *mini, char *str)
{
	struct stat	path_stat;
	char		*path;

	path = pre_trim(str, ' ');
	if (path == NULL || ft_strcmp(path, "") == 0)
	{
		if (ft_strcmp(str, "") != 0)
			free(str);
		return (ft_exit(mini, "ambiguous redirect", 1, 0), false);
	}
	if (stat(path, &path_stat) == -1)
		return (true);
	if (S_ISDIR(path_stat.st_mode))
	{
		if (ft_strcmp(str, "..") == 0)
			ft_exit(mini, "command not found", 127, 0);
		else
			ft_exit(mini, "Is a directory", 1, 0);
		return (close_fds(), false);
	}
	return (true);
}

int	input_check(t_mini *mini, char **cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i][0] == ' ' || cmds[i][0] == '>' || cmds[i][0] == '<')
		{
			i++;
			continue ;
		}
		else if (input_util(mini, cmds, i) == false)
		{
			ft_exit(mini, "command not found", 127, 0);
			return (false);
		}
		i++;
	}
	return (true);
}

int	builtin_check(char *str)
{
	char	*valid[10];
	size_t	i;

	i = 0;
	if (str == NULL || str == NULL)
		return (EXIT_FAILURE);
	valid[0] = "cd";
	valid[1] = "pwd";
	valid[2] = "echo";
	valid[3] = "env";
	valid[4] = "exit";
	valid[5] = "export";
	valid[6] = "unset";
	valid[7] = "clear";
	valid[8] = "bash";
	valid[9] = NULL;
	while (valid[i] != NULL)
	{
		if (ft_strcmp(valid[i], str) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	*str_cleaner(char *cmd, int i)
{
	char	*arg;
	char	*temp;

	(void)i;
	temp = pre_trim(cmd, ' ');
	if (temp == NULL)
		return (NULL);
	if (ft_strchr(temp, '$') != NULL)
	{
		arg = pre_trim(temp, '$');
		if (arg == NULL)
			return (free(temp), NULL);
	}
	arg = ft_strtrim(temp, "\"'");
	if (arg == NULL)
		return (free(temp), NULL);
	return (arg);
}
