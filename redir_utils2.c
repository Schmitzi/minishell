/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:03:31 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:30:29 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_mini *mini, int *i)
{
	if (mini->heredoc == true)
	{
		if (heredoc_init(mini) == false)
			return (free_doc(mini->heredocs), false);
		(*i)++;
	}
	return (true);
}

int	handle_redir_out(t_mini *mini, int *i)
{
	if (mini->heredoc == false)
		if (redir_util1(mini, *i) == false)
			return (false);
	(*i)++;
	return (true);
}

int	handle_redir_in(t_mini *mini, int *i)
{
	if (redir_util2(mini, *i) == false || redir_in(mini) == false)
	{
		return (false);
	}
	(*i)++;
	return (true);
}

int	redir_dir(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[i] != NULL)
	{
		if (ft_strcmp(mini->args[i], "<<") == 0)
			mini->heredoc = true;
		else if (ft_strcmp(mini->args[i], ">") == 0 || \
			ft_strcmp(mini->args[i], ">>") == 0)
		{
			if (handle_redir_out(mini, &i) == false)
				return (false);
		}
		else if (ft_strcmp(mini->args[i], "<") == 0
			&& mini->heredoc == false)
		{
			if (handle_redir_in(mini, &i) == false)
				return (false);
		}
		i++;
	}
	if (handle_heredoc(mini, &i) == false)
		return (false);
	redir_loop(mini);
	return (true);
}

int	start_redir(t_mini *mini)
{
	if (mini->args && syntax_redir(mini, mini->args) == true && \
		syntax_heredoc(mini->args) == true)
	{
		if (redir_count(mini) == false)
			return (false);
		if (find_outfile(mini) == false)
			return (false);
	}
	return (true);
}
