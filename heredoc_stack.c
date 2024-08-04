/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:28:05 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:37:17 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_run(t_mini *mini)
{
	mini->hd_count = 0;
	mini->heredoc = false;
	while (mini->heredocs[mini->hd_i + 1] != NULL)
	{
		while (1)
		{
			if (grab_line(mini, mini->heredocs[mini->hd_i]) == 1)
			{
				if (g_sig != 0)
				{
					mini->i = mini->count;
					return (false);
				}
				else
					break ;
			}
		}
		mini->hd_i++;
	}
	return (true);
}

static int	create_hd(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini->args[i])
	{
		if (ft_strcmp(mini->args[i], "<<") == 0)
			j++;
		i++;
	}
	mini->heredocs = (t_doc **)malloc(sizeof(t_doc *) * (j + 1));
	if (mini->heredocs == NULL)
		return (ft_exit(mini, "heredocs_malloc", 1, 0), false);
	return (true);
}

int	stacker(t_mini *mini, int i, int j)
{
	char	*tmp;

	mini->heredocs[j] = (t_doc *)malloc(sizeof(t_doc));
	if (mini->heredocs[j] == NULL)
		return (ft_exit(mini, "malloc failed", 1, 0), false);
	if (ft_strcmp(mini->args[i + 1], "\"\"") == 0 || \
		ft_strcmp(mini->args[i + 1], "\'\'") == 0)
		mini->heredocs[j]->delim = ft_strdup("");
	else
		mini->heredocs[j]->delim = ft_strdup(mini->args[i + 1]);
	if (mini->heredocs[j]->delim == NULL)
		(free(mini->heredocs[j]->delim),
			mini->heredocs[j]->delim = ft_strdup(""));
	if (ft_strchr(mini->heredocs[j]->delim, '\'') == 0 || \
		ft_strchr(mini->heredocs[j]->delim, '\"') == 0)
	{
		tmp = ft_strdup(mini->heredocs[j]->delim);
		free(mini->heredocs[j]->delim);
		mini->heredocs[j]->delim = expand_string(mini, tmp);
		if (mini->heredocs[j]->delim == NULL)
			(free(mini->heredocs[j]->delim),
				mini->heredocs[j]->delim = ft_strdup(""));
		free(tmp);
	}
	return (true);
}

int	stack_heredocs(t_mini *mini)
{
	int		i;
	int		j;

	if (create_hd(mini) == false)
		return (false);
	i = 0;
	j = 0;
	while (mini->args[i] != NULL)
	{
		if (ft_strcmp(mini->args[i], "<<") == 0)
		{
			stacker(mini, i, j);
			j++;
		}
		i++;
	}
	mini->heredocs[j - 1]->delim
		= remove_quotes(mini, mini->heredocs[j - 1]->delim);
	return (mini->heredoc = true, mini->heredocs[j] = NULL, true);
}

pid_t	heredoc_child(t_mini *mini)
{
	pid_t	pid;

	if (mini->args[0] && is_builtin(mini) == true)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
