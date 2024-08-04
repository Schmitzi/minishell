/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:34 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:36:21 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpid(void)
{
	int		fd;
	ssize_t	bytes_read;
	char	*pid_str;
	char	*path;
	char	buffer[256];

	path = ft_strdup("/proc/self/stat");
	if (path == NULL)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), free(path), NULL);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
	{
		close(fd);
		return (perror("read"), free(path), NULL);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	pid_str = pre_trim(buffer, ' ');
	if (pid_str != NULL)
		return (free(path), pid_str);
	return (free(path), NULL);
}

int	correct_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i] != NULL)
		i++;
	if (i == 0)
	{
		if (edit_env(mini, "_", " ") == false)
			return (false);
	}
	if (mini->path == NULL)
	{
		if (i > 0)
		{
			if (edit_env(mini, "_", mini->args[count_args(mini->args) - 1]))
				return (false);
		}
		else
			if (edit_env(mini, "_", mini->args[0]))
				return (false);
	}
	if (edit_env(mini, "_", mini->path) == false)
		return (false);
	return (true);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (-1);
	while (args[i] != NULL)
		i++;
	return (i);
}

int	white_check(char **str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == ' ' || str[i][j] == '\"' || \
			str[i][j] == '\'') && flag != 1)
				flag = 2;
			else
				flag = 1;
			j++;
		}
		i++;
	}
	if (flag == 1)
		return (false);
	return (true);
}
