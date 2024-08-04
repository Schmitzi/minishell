/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:34 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 13:22:54 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *mini)
{
	size_t	i;
	int		fd;

	i = 0;
	if (mini->i == mini->count -1)
		fd = 1;
	else
		fd = mini->fd[mini->i][1];
	if (mini->args[0] == NULL)
	{
		ft_exit(mini, "bad env", 1, 0);
		return ;
	}
	while (mini->env[i] != NULL)
	{
		if (ft_strchr(mini->env[i], '=') != 0)
		{
			ft_putstr_fd(mini->env[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
}

char	*ft_getenv(t_mini *mini, char *env)
{
	int		i;
	int		len;

	i = 0;
	if (env == NULL)
		return (NULL);
	if (ft_strchr(env, ' ') != NULL)
		return (env);
	while (mini->env[i])
	{
		len = ft_strlen(env);
		if (mini->env[i] && ft_strncmp(env, mini->env[i], len) == 0 && \
			mini->env[i][len] == '=')
		{
			if (mini->env[i][len + 1] != '\0')
				return (mini->env[i] + (len + 1));
			else
				return ("");
		}
		i++;
	}
	return ("");
}
