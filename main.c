/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:37:19 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 16:16:19 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_env(t_mini *mini, char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[count] != NULL)
		count++;
	mini->env = malloc((count + 1) * sizeof(char *));
	if (mini->env == NULL)
		return (false);
	while (i < count)
	{
		mini->env[i] = malloc(ft_strlen(env[i]) + 1);
		if (mini->env[i] == NULL)
			return (free_array(mini->env), false);
		ft_strcpy(mini->env[i], env[i]);
		if (mini->env[i] == NULL)
			return (false);
		i++;
	}
	mini->env[i] = NULL;
	return (true);
}

static int	build_env(t_mini *mini, char **env)
{
	if (save_env(mini, env) == false)
		return (false);
	if (mini->env == NULL)
		return (cleanup_mini(mini), false);
	if (reset_shlvl(mini) == false)
		return (false);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	t_mode	mode;

	((void)argc, (void)argv, mode = 0);
	if (!env[0])
	{
		if (backup_env(&mini) == false)
			exit(1);
	}
	else
	{
		if (build_env(&mini, env) == false)
			exit(1);
	}
	if (mini_init(&mini) == true)
	{
		(print_header(), ft_mode(&mini, mode));
		if (g_sig == SIGINT || g_sig == SIGQUIT)
			sig_reset(&mini, g_sig);
		prompt(&mini);
	}
	ft_freemain(&mini);
	return (mini.errno_code);
}

static int	set_oldpwd(t_mini *mini)
{
	char	*temp;

	temp = ft_strdup(ft_getenv(mini, "OLDPWD"));
	if (temp == NULL)
	{
		add_env(mini, "OLDPWD");
		mini->oldpwd = ft_strdup("");
		if (mini->oldpwd == NULL)
		{
			free(temp);
			return (ft_exit(mini, "malloc failed", errno, 0), 0);
		}
	}
	else
	{
		mini->oldpwd = ft_strdup(temp);
		if (mini->oldpwd == NULL)
		{
			free(temp);
			return (ft_exit(mini, "malloc failed", errno, 0), 0);
		}
	}
	free(temp);
	return (true);
}

int	reset_shlvl(t_mini *mini)
{
	int		new;
	char	*value;
	char	*temp;

	mini->index = 0;
	if (set_oldpwd(mini) == false)
		return (false);
	temp = ft_getenv(mini, "SHLVL");
	if (temp == NULL)
		return (ft_exit(mini, "edit env fail", 1, 0), false);
	new = (ft_atoi(temp) + 1);
	if (new >= 10000)
	{
		ft_putstr_fd("warning: shell level too high, resetting to 1", 2);
		new = 1;
	}
	value = ft_itoa(new);
	if (value == NULL)
		return (false);
	if (edit_env(mini, "SHLVL", value) == false)
		return (free(temp), free(value), false);
	free(value);
	return (true);
}
