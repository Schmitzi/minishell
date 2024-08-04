/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:34:18 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 14:10:04 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_loop(t_mini *mini, char *arg)
{
	char	*value;
	char	*key;

	if (ft_strcmp(arg, mini->env[mini->index]) == 0)
		return (true);
	if (ft_strchr(arg, '=') != 0)
	{
		value = post_trim(arg, '=');
		if (value == NULL)
			return (false);
		if (ft_strchr(value, '$') != 0)
		{
			value = ft_strtrim(value, "$");
			if (value == NULL)
				return (free(value), false);
		}
		key = pre_trim(arg, '=');
		if (key == NULL)
			return (free(value), false);
		if (edit_env(mini, key, value) == false)
			return (free(value), free(key), false);
		(free(value), free(key));
	}
	return (true);
}

int	process_arg(t_mini *mini, char *arg)
{
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strcmp(mini->env[i], arg) == 0)
			return (true);
		i++;
	}
	if (ft_strcmp(arg, "") == 0)
		return (true);
	if (export_name(mini, arg) == true)
	{
		if (env_check(mini, arg) == true)
		{
			if (process_loop(mini, arg) == false && ft_strchr(arg, '=') != 0)
				return (false);
		}
		else
			if (add_env(mini, arg) == false)
				return (false);
	}
	else
		return (false);
	return (true);
}

int	ft_export(t_mini *mini)
{
	int		i;
	int		flag;
	char	*arg;

	i = 1;
	flag = false;
	if (mini->args[1] == NULL)
		export_unset(mini);
	else if (mini->count != 1 || mini->args[1] == NULL)
		return (true);
	else
	{
		while (mini->args[i] != NULL)
		{
			arg = ft_strdup(mini->args[i]);
			if (arg == NULL)
				return (false);
			if (process_arg(mini, arg) == false)
				flag = true;
			(free(arg), i++);
		}
	}
	if (flag == true)
		return (false);
	return (true);
}

int	env_check(t_mini *mini, char *arg)
{
	int		i;
	char	*name;

	i = 0;
	if (ft_strchr(arg, '=') != 0)
		name = pre_trim(arg, '=');
	else
		name = ft_strdup(arg);
	if (name == NULL)
		return (false);
	while (mini->env[i] != NULL)
	{
		if (ft_strncmp(mini->env[i], name, ft_strlen(name)) == 0)
			return (free(name), true);
		i++;
	}
	free(name);
	return (false);
}

int	export_name(t_mini *mini, char *args)
{
	char	*res;

	if (ft_strchr(args, '=') != 0 && args[0] != '=')
	{
		res = pre_trim(args, '=');
		if (res == NULL)
			return (false);
	}
	else
		res = ft_strdup(args);
	if (res == NULL)
		return (false);
	if ((args[0] >= '0' && args[0] <= '9') || args[0] == '.' || \
		args[0] == '-' || res[ft_strlen(res) - 1] == '-' || args[0] == '=')
	{
		ft_exit(mini, "not a valid identifier", 1, 0);
		return (free(res), false);
	}
	if (ft_strncmp(args, "_=", 2) == 0)
		return (free(res), false);
	return (free(res), true);
}
