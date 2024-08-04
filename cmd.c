/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:52:27 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 14:05:08 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	info_init(t_mini *mini)
{
	mini->info.i = 0;
	mini->info.j = 0;
	mini->info.quotes = 0;
	mini->info.quote_type = 0;
	if (cmd_mem(mini) == false)
		return (free(mini->cmds), false);
	return (true);
}

void	handle_quotes(t_mini *mini)
{
	if (mini->input[mini->info.i] == '\'' || mini->input[mini->info.i] == '\"')
	{
		if (mini->info.quotes
			&& mini->input[mini->info.i] == mini->info.quote_type)
		{
			mini->info.quotes = 0;
			mini->info.quote_type = 0;
		}
		else if (!mini->info.quotes)
		{
			mini->info.quotes = 1;
			mini->info.quote_type = mini->input[mini->info.i];
		}
	}
	mini->cmds[mini->info.j][(mini->info.k)++] = mini->input[(mini->info.i)++];
}

void	handle_pipe(t_mini *mini)
{
	if (mini->input[mini->info.i] == '|')
		(mini->info.i)++;
}

int	cmd_mem(t_mini *mini)
{
	mini->cmds = (char **)malloc(sizeof(char *) * (mini->count + 1));
	if (mini->cmds == NULL)
		return (false);
	return (true);
}

int	cmd_split(t_mini *mini)
{
	if (info_init(mini) == false)
		return (false);
	while (mini->info.i < ft_strlen(mini->input))
	{
		mini->info.k = 0;
		mini->cmds[mini->info.j] = (char *)malloc(sizeof(char)
				* (ft_strlen(mini->input) + 1));
		if (mini->cmds[mini->info.j] == NULL)
		{
			ft_exit(mini, "Memory allocation failed for cmd", errno, 0);
			return (free(mini->cmds[mini->info.j]), false);
		}
		while (mini->input[mini->info.i] == ' ')
			mini->info.i++;
		while (mini->input[mini->info.i] && \
			(mini->input[mini->info.i] != '|' || mini->info.quotes))
			handle_quotes(mini);
		mini->cmds[mini->info.j][mini->info.k] = '\0';
		if (!mini->info.quotes)
			handle_pipe(mini);
		mini->info.j++;
	}
	mini->cmds[mini->info.j] = NULL;
	return (free(mini->cmds[mini->info.j]), true);
}
