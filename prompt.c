/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:03:09 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 18:25:10 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	white_skip(char *input)
{
	int	i;

	i = 0;
	if (ft_strcmp(input, "\"\"") == 0 || ft_strcmp(input, "\'\'") == 0)
		return (true);
	while (input[i] != '\0')
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (false);
		i++;
	}
	if (i > 0)
		return (true);
	return (false);
}

void	prompt(t_mini *mini)
{
	while (1)
	{
		shlvl_check(mini);
		if (mini->exit == true)
			return ;
		if (take_input(mini) == false || mini->input == NULL)
			break ;
		if (ft_strcmp(mini->input, "") == 0 || white_skip(mini->input) == true)
			continue ;
		if (mini->input[0] != '\0')
		{
			if (syntax_check(mini->input) == false)
			{
				(free(mini->input), ft_exit(mini, "syntax error", 2, 0));
				continue ;
			}
			arg_count(mini);
			if (cmd_split(mini) == false)
				return (free_array(mini->cmds), free(mini->input));
			if (ft_calling(mini) == false)
				break ;
		}
		else
			return (ft_exit(mini, "syntax error", 2, 0));
	}
}

int	take_input(t_mini *mini)
{
	char	*input;

	input = input_builder(mini);
	if (input == NULL)
		return (ft_exit(mini, "input failed", errno, 0), false);
	ft_mode(mini, NO_INTER);
	if (g_sig == SIGINT || g_sig == SIGQUIT)
	{
		sig_reset(mini, g_sig);
		if (g_sig == SIGQUIT)
			cleanup_mini(mini);
	}
	mini->input = readline(input);
	ft_mode(mini, INTER);
	if (g_sig == SIGINT || g_sig == SIGQUIT)
	{
		sig_reset(mini, g_sig);
		if (g_sig == SIGQUIT)
			cleanup_mini(mini);
	}
	if (mini->input == NULL)
		return (free(input), false);
	if (ft_strcmp(mini->input, "") == 0)
		return (free(input), true);
	return (add_history(mini->input), free(input), true);
}

static void	pre_exit(t_mini *mini)
{
	if (mini->i == mini->count + 1)
	{
		if (mini->args && mini->args[0] && \
			ft_strcmp(mini->args[0], "exit") == 0 && \
			mini->count == 1 && mini->heredoc == false && \
			mini->args[2] == NULL)
			ft_builtin_exit(mini);
	}
}

int	ft_calling(t_mini *mini)
{
	if (init_pipes(mini) == false)
		return (false);
	mini->hd_count = heredoc_count(mini);
	while (mini->i < mini->count)
	{
		if (set_args(mini) == true)
		{
			if (mini->exit == 1)
				return (true);
			pre_exit(mini);
			mini->pid[mini->i] = create_child(mini);
			if (mini->pid[mini->i] == 0)
				child_process(mini);
			else
				parent_process(mini);
		}
		else
		{
			free(mini->path);
			(free_array(mini->args), free_array(mini->path_entries));
		}
		mini->i++;
	}
	mini->i = 0;
	return (free_pipes(mini), free_array(mini->cmds), true);
}
