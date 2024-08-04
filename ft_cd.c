/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schmitzi <schmitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:52:24 by schmitzi          #+#    #+#             */
/*   Updated: 2024/07/04 23:44:56 by schmitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_tools(t_mini *mini)
{
	if (ft_getenv(mini, "PWD") == NULL)
		add_env(mini, "PWD");
	if (ft_getenv(mini, "OLDPWD") == NULL)
		add_env(mini, "OLDPWD");
	if (!mini->args[1] || ft_strcmp(mini->args[1], "") == 0)
	{
		if (cd_add_arg(mini) == false)
			return (false);
		free(mini->args[1]);
		mini->args[1] = ft_strdup(ft_getenv(mini, "HOME"));
		if (mini->args[1] == NULL)
			return (false);
	}
	if (mini->args[1][0] == '~')
		if (cd_tilda(mini) == false)
			return (false);
	return (true);
}

int	cd_dot_dot(t_mini *mini, char *dir)
{
	if (mini->oldpwd)
		free(mini->oldpwd);
	mini->oldpwd = ft_strdup(mini->cwd);
	if (mini->oldpwd == NULL)
		return (ft_exit(mini, "malloc failed", errno, 0), false);
	edit_env(mini, "OLDPWD", mini->cwd);
	if (mini->oldpwd == NULL)
		return (ft_exit(mini, "malloc failed", errno, 0), false);
	if (access(dir, F_OK) == -1)
		return (ft_exit(mini, "No such file or directory", 1, 0), false);
	if (chdir(dir) != 0)
		return (ft_exit(mini, "No such file or directory", 1, 0), false);
	edit_env(mini, "PWD", dir);
	free(mini->cwd);
	mini->cwd = ft_strdup(dir);
	if (mini->cwd == NULL)
		return (ft_exit(mini, "malloc failed", errno, 0), false);
	return (true);
}

int	find_good_dir(t_mini *mini, char *str)
{
	int		i;
	char	*parent_dir;

	parent_dir = malloc(ft_strlen(str) + 1);
	if (parent_dir == NULL)
		return (ft_exit(mini, "malloc failed", errno, 0), false);
	ft_strcpy(parent_dir, str);
	i = ft_strlen(parent_dir) - 1;
	while (i >= 0)
	{
		if (ft_strlen(parent_dir) > 1 && parent_dir[i - 1] == '/')
		{
			parent_dir[i] = '\0';
			if (ft_strcmp(parent_dir, "/") != 0 && chdir(parent_dir) == 0)
				break ;
		}
		i--;
	}
	cd_dot_dot(mini, parent_dir);
	free(parent_dir);
	return (true);
}

int	cd_dash(t_mini *mini)
{
	if (mini->args[1] && ft_strcmp(mini->args[1], "-") == 0)
	{
		if (mini->oldpwd && ft_strcmp(mini->oldpwd, "") == 0)
			return (ft_exit(mini, "OLDPWD not set", 1, 0), false);
		if (chdir(mini->oldpwd) == -1)
			return (ft_exit(mini, "No such file or directory", 1, 0), false);
		edit_env(mini, "OLDPWD", mini->cwd);
		free(mini->oldpwd);
		mini->oldpwd = ft_strdup(mini->cwd);
		if (mini->oldpwd == NULL)
			return (ft_exit(mini, "malloc failed", errno, 0), false);
		free(mini->cwd);
		mini->cwd = getcwd(NULL, 0);
		if (mini->cwd == NULL)
			return (ft_exit(mini, "getcwd failed", errno, 0), false);
		edit_env(mini, "PWD", mini->cwd);
		return (true);
	}
	return (true);
}

int	ft_cd(t_mini *mini)
{
	if (mini->args[1] != NULL && mini->args[2] != NULL)
		return (ft_exit(mini, "too many arguments", 1, 0), false);
	if (mini->count != 1)
	{
		if (access(mini->args[1], F_OK) != -1)
			return (ft_exit(mini, "No such file or directory", 1, 0), true);
	}
	if (cd_tools(mini) == false)
		return (false);
	else if (mini->args[1] && ft_strcmp(mini->args[1], "-") == 0)
		return (cd_dash(mini));
	if (mini->args[1] && ft_strcmp(mini->args[1], "..") == 0)
		return (find_good_dir(mini, mini->cwd));
	else
	{
		if (mini->oldpwd)
			free(mini->oldpwd);
		mini->oldpwd = getcwd(NULL, 0);
		if (chdir(mini->args[1]) != 0)
			return (ft_exit(mini, "No such file or directory", 1, 0), false);
		(edit_env(mini, "OLDPWD", mini->cwd), free(mini->cwd));
		mini->cwd = getcwd(NULL, 0);
		edit_env(mini, "PWD", mini->cwd);
	}
	return (true);
}
