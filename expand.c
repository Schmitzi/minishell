/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:15:13 by miturk            #+#    #+#             */
/*   Updated: 2024/07/19 13:44:46 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_char(t_sort *args, char *arg)
{
	args->flag = 0;
	if ((arg[args->i] == '"' || arg[args->i] == '\''))
	{
		args->flag = 1;
		if (args->in_quotes == arg[args->i])
			args->in_quotes = 0;
		else if (args->in_quotes == 0)
			args->in_quotes = arg[args->i];
		else
			args->new_str[args->j++] = arg[args->i];
	}
	else if (arg[args->i] == '$')
		process_dollar_sign(args, arg);
	else
		args->new_str[args->j++] = arg[args->i];
}

char	*remove_quotes(t_mini *mini, char *arg)
{
	if (arg == NULL)
		return (NULL);
	if (init_sort(&mini->sort, arg) == false)
		return (free(arg), NULL);
	while (mini->sort.i < mini->sort.len)
	{
		process_char(&mini->sort, arg);
		if (mini->sort.flag == 1)
			mini->qflag = 1;
		mini->sort.i++;
	}
	mini->sort.new_str[mini->sort.j] = '\0';
	free(arg);
	if (ft_strlen(mini->sort.new_str) == 0)
		return (free(mini->sort.new_str), "\0");
	return (mini->sort.new_str);
}

int	trim(t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	if (mini->args[0] == NULL)
		return (true);
	while (mini->args[i] != NULL)
	{
		temp = ft_strdup(mini->args[i]);
		if (temp == NULL)
			return (ft_exit(mini, "Memory allocation error", errno, 0), false);
		if (ft_strcmp(mini->args[i], "") != 0)
			free(mini->args[i]);
		mini->args[i] = remove_quotes(mini, temp);
		i++;
	}
	return (true);
}

int	access_check(t_mini *mini, char *input)
{
	char	*dir;
	char	*arg;
	int		i;

	i = 0;
	while (mini->path_entries[i])
	{
		arg = str_cleaner(input, i);
		dir = ft_strjoin(mini->path_entries[i], "/");
		dir = ft_strjoin(dir, arg);
		if (dir == NULL)
		{
			free(arg);
			ft_exit(mini, "Memory allocation error input", errno, 0);
		}
		if (access(dir, X_OK) != -1)
			return (true);
		i++;
	}
	if (!mini->path_entries[i] && input[0] != '$' && builtin_check(arg) != true)
		return (free(arg), free(dir), false);
	return (true);
}

int	pipe_exit(t_mini *mini, long long error)
{
	if (mini->count != 1 && mini->args)
	{
		if (count_args(mini->args) > 2)
			return (ft_exit(mini, "too many arguments", 1, 0), true);
		if (!mini->args[1] || !mini->args || \
			check_num(mini, mini->args[1]) == false)
			return (true);
		if (ft_strcmp(mini->args[1], "") == 0)
			ft_exit(mini, NULL, 1, 0);
		else
		{
			error = ft_atoll(mini->args[1]);
			if (error >= 9223372036854775807LL)
				return (ft_exit(mini, "numeric argument required", 2, 0), true);
			while (error > 255)
				error %= 256;
		}
		mini->errno_code = error;
	}
	else
		return (false);
	return (true);
}
