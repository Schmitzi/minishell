/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:17:38 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 18:24:31 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alias(t_mini *mini)
{
	if (mini->args == NULL || mini->args[0] == NULL)
		ft_exit(mini, "alias no args", errno, 0);
	else if (ft_strcmp(mini->args[0], "cd") == 0)
		return (ft_cd(mini));
	else if (ft_strcmp(mini->args[0], "pwd") == 0)
		ft_getcwd(mini);
	else if (ft_strcmp(mini->args[0], "echo") == 0)
		ft_echo(mini);
	else if (ft_strncmp(mini->args[0], "env", 3) == 0)
		ft_env(mini);
	else if (ft_strcmp(mini->args[0], "exit") == 0)
		return (ft_builtin_exit(mini));
	else if (ft_strcmp(mini->args[0], "export") == 0)
		return (ft_export(mini));
	else if (ft_strcmp(mini->args[0], "unset") == 0)
		ft_unset(mini);
	else
		return (false);
	mini->errno_code = 0;
	return (true);
}

void	ft_getcwd(t_mini *mini)
{
	ft_putstr_fd(mini->cwd, 1);
	ft_putstr_fd("\n", 1);
	return ;
}

void	shlvl_check(t_mini *mini)
{
	int		i;
	char	*shlvl;
	char	*new_shlvl;

	i = 0;
	shlvl = ft_getenv(mini, "SHLVL");
	if (ft_atoi(shlvl) > 9999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(shlvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		new_shlvl = ft_itoa(1);
		while (mini->env[i] != NULL)
		{
			if (ft_strncmp(mini->env[i], "SHLVL=", 6) == 0)
			{
				free(mini->env[i]);
				mini->env[i] = ft_strjoin("SHLVL=", new_shlvl);
				free(new_shlvl);
				break ;
			}
			i++;
		}
	}
}

char	**bubble_sort(char **arr)
{
	int		i;
	int		j;
	int		n;
	char	*temp;

	i = 0;
	n = 0;
	while (arr[n] != NULL)
		n++;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
