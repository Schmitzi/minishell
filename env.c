/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:04:28 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 14:06:31 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	edit_env(t_mini *mini, char *key, char *value)
{
	int		i;

	i = 0;
	while (mini->env[i] != NULL)
	{
		if (ft_strncmp(mini->env[i], key, ft_strlen(key)) == 0)
		{
			if (value != NULL)
			{
				if (edit_tool(mini, key, value, i) == false)
					return (free(value), false);
			}
			else
				(free(mini->env[i]), mini->env[i] = ft_strdup(key));
			return (true);
		}
		i++;
	}
	return (false);
}

int	add_env(t_mini *mini, char *arg)
{
	char	**temp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (mini->env[len] != NULL)
		len++;
	temp = (char **)malloc(sizeof(char *) * (len + 2));
	if (temp == NULL)
		return (ft_exit(mini, "add_env_malloc", errno, 0), false);
	while (mini->env[i] != NULL)
	{
		temp[i] = ft_strdup(mini->env[i]);
		if (temp[i] == NULL)
			return (ft_exit(mini, "add_env_malloc", errno, 0), false);
		i++;
	}
	temp[i] = ft_strdup(arg);
	if (temp[i] == NULL)
		return (ft_exit(mini, "add_env_malloc", errno, 0), false);
	temp[i + 1] = NULL;
	if (mini->env)
		free_array(mini->env);
	return (mini->env = temp, true);
}

int	backup_env(t_mini *mini)
{
	int		i;
	char	*env[6];

	i = 0;
	env[0] = "OLDPWD";
	env[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[2] = "SHLVL=0";
	env[3] = "_=/usr/bin/env";
	env[4] = ft_strjoin("PATH=", "/usr/local/bin:/usr/local/sbin:");
	env[4] = ft_strjoin(env[4], "/usr/bin:/usr/sbin:/bin:/sbin");
	env[5] = NULL;
	mini->env = malloc(sizeof(char *) * 7);
	if (mini->env == NULL)
		return (ft_exit(mini, "Malloc failed", 1, 0), false);
	while (env[i])
	{
		mini->env[i] = ft_strdup(env[i]);
		if (mini->env[i] == NULL)
			return (ft_exit(mini, "Malloc failed", 1, 0), false);
		i++;
	}
	mini->env[i] = NULL;
	reset_shlvl(mini);
	return (true);
}

static int	print_export(char **sorted, int fd)
{
	int		i;
	char	*pre;
	char	*post;

	i = -1;
	while (sorted[++i] != NULL)
	{
		if (ft_strchr(sorted[i], '=') != 0 && \
			ft_strncmp(sorted[i], "_=", 2) != 0)
		{
			pre = pre_trim(sorted[i], '=');
			if (pre == NULL)
				return (free_array(sorted), false);
			(ft_putstr_fd("declare -x ", fd), ft_putstr_fd(pre, fd));
			post = post_trim(sorted[i], '=');
			if (post == NULL)
				return (free(pre), free_array(sorted), false);
			(ft_putstr_fd("=\"", fd), ft_putstr_fd(post, fd));
			(ft_putstr_fd("\"\n", fd), free(post), free(pre));
		}
		else if (sorted[i][0] != '_')
			(ft_putstr_fd("declare -x ", fd), ft_putstr_fd(sorted[i], fd), \
				ft_putstr_fd("\n", fd));
	}
	return (free_array(sorted), true);
}

void	export_unset(t_mini *mini)
{
	int		i;
	int		fd;
	char	**sorted;

	i = 0;
	while (mini->env[i])
		i++;
	sorted = (char **)malloc(sizeof(char *) * (i + 1));
	if (sorted == NULL)
		return (ft_exit(mini, "Malloc failed", 1, 0));
	sorted[i] = NULL;
	i = 0;
	while (mini->env[i])
	{
		sorted[i] = ft_strdup(mini->env[i]);
		if (sorted[i] == NULL)
			return (ft_exit(mini, "Malloc failed", 1, 0), free_array(sorted));
		i++;
	}
	sorted = bubble_sort(sorted);
	if (sorted == NULL)
		return (ft_exit(mini, "Bubble sort failed", 1, 0), free_array(sorted));
	fd = echo_tool(mini);
	if (print_export(sorted, fd) == false)
		ft_exit(mini, "Print export failed", 1, false);
}
