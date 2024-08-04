/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:12:13 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/03 15:51:47 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_add_arg(t_mini *mini)
{
	int		i;
	int		len;
	char	**new_args;

	i = 0;
	len = 0;
	while (mini->args[len] != NULL)
		len++;
	new_args = malloc(sizeof(char *) * (len + 2));
	if (new_args == NULL)
		return (ft_exit(mini, "malloc failed", errno, 0), false);
	while (i < len)
	{
		new_args[i] = ft_strdup(mini->args[i]);
		if (new_args[i] == NULL)
		{
			free_array(new_args);
			return (ft_exit(mini, "malloc failed", errno, 0), false);
		}
		i++;
	}
	while (i < len + 2)
		new_args[i++] = NULL;
	free_array(mini->args);
	return (mini->args = new_args, true);
}

int	cd_tilda(t_mini *mini)
{
	char	*temp;
	char	*home;

	temp = ft_strdup(mini->args[1]);
	if (temp == NULL)
		return (false);
	free(mini->args[1]);
	home = getenv("HOME");
	mini->args[1] = ft_strjoin(home, temp + 1);
	if (mini->args[1] == NULL)
		return (false);
	free(temp);
	if (mini->args[1] == NULL)
		return (false);
	mini->args[2] = NULL;
	return (true);
}
