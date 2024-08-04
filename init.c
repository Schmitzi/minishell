/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:55:29 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/06 13:53:34 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_init(t_mini *mini)
{
	mini->cwd = getcwd(NULL, 0);
	if (mini->cwd == NULL)
		return (free(mini->cwd), false);
	mini->path = NULL;
	mini->input = NULL;
	mini->exit = 0;
	mini->orig_stdin = dup(STDIN_FILENO);
	mini->orig_stdout = dup(STDOUT_FILENO);
	mini->heredoc = false;
	mini->errno_code = 0;
	mini->i = 0;
	mini->redir = false;
	mini->mode = 0;
	mini->pid = NULL;
	mini->status = 0;
	mini->fd = NULL;
	mini->outfile = NULL;
	mini->infile = NULL;
	mini->hd_count = 0;
	mini->hd_i = 0;
	mini->qflag = 0;
	mini->curr_pid = ft_getpid();
	return (true);
}

int	init_pipes(t_mini *mini)
{
	int	i;

	i = 0;
	mini->pid = (int *)malloc(sizeof(int) * mini->count);
	if (mini->pid == NULL)
		return (false);
	mini->fd = (int **)malloc(sizeof(int *) * (mini->count + 1));
	if (mini->fd == NULL)
		return (free(mini->pid), ft_exit(mini, NULL, 1, 0), false);
	while (i < mini->count)
	{
		mini->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!mini->fd[i])
			return (false);
		if (pipe(mini->fd[i]) == -1)
		{
			mini->count = i;
			free_pipes(mini);
			return (free_array(mini->cmds), ft_exit(mini, "pipes failed", \
				666, 0), false);
		}
		i++;
	}
	mini->fd[mini->count] = NULL;
	return (true);
}

static long long	ft_process_digits(const char *str, int i, bool neg)
{
	long long	result;
	long long	prev_result;

	result = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (2);
		prev_result = result;
		result = result * 10 + (str[i] - '0');
		if (result < prev_result)
			return (2);
		i++;
	}
	if (neg)
		result = -result;
	return (result);
}

long long	ft_atoll(const char *str)
{
	int		i;
	bool	neg;

	neg = false;
	i = skip_space(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = true;
		i++;
	}
	return (ft_process_digits(str, i, neg));
}

void	re_arg(t_mini *mini)
{
	int		i;
	char	*new_input;
	char	*temp;

	i = 1;
	new_input = ft_strdup(mini->args[0]);
	if (new_input == NULL)
		return ;
	while (mini->args[i])
	{
		temp = new_input;
		new_input = ft_strjoin(new_input, " ");
		if (new_input == NULL)
			return (free(new_input), free(temp));
		(free(temp), temp = new_input);
		new_input = ft_strjoin(new_input, mini->args[i]);
		if (new_input == NULL)
			return (free(new_input), free(temp));
		(free(temp), i++);
	}
	(free_array(mini->args), free(mini->cmds[mini->i]));
	mini->cmds[mini->i] = ft_strdup(new_input);
	if (mini->cmds[mini->i] == NULL)
		return (free(new_input));
	(tokenize(mini), free(new_input));
}
