/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schmitzi <schmitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:12:55 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/09 12:17:46 by schmitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_mini *mini)
{
	char	*valid[8];
	size_t	i;

	i = 0;
	if (mini->args[0] == NULL)
		return (false);
	valid[0] = "cd";
	valid[1] = "pwd";
	valid[2] = "echo";
	valid[3] = "env";
	valid[4] = "exit";
	valid[5] = "export";
	valid[6] = "unset";
	valid[7] = NULL;
	while (valid[i] != NULL)
	{
		if (ft_strcmp(valid[i], mini->args[0]) == 0)
			return (true);
		i++;
	}
	return (false);
}

static int	n_check(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (str[i] != NULL && str[i][0] == '-' && str[i][1] == 'n')
	{
		while (str[i][j] != '\0' && str[i][j] == 'n')
			j++;
		if (str[i][j] != '\0')
			break ;
		i++;
		j = 1;
	}
	return (i);
}

int	echo_tool(t_mini *mini)
{
	int	fd;

	if (mini->redir == true)
		fd = 1;
	else if (mini->i == mini->count -1)
		fd = 1;
	else
		fd = mini->fd[mini->i][1];
	return (fd);
}

void	ft_echo(t_mini *mini)
{
	size_t	i;
	int		fd;
	int		nl;

	i = 0;
	nl = true;
	fd = echo_tool(mini);
	i += n_check(mini->args);
	if (i == 1)
		nl = false;
	while (mini->args[i] != NULL)
	{
		if (mini->args[i][0] != '\0')
			ft_putstr_fd(mini->args[i], fd);
		if (mini->args[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (mini->infile && !mini->args[1])
		return ;
	if (nl == false)
		ft_putstr_fd("\n", fd);
	mini->errno_code = 0;
}

int	ft_builtin_exit(t_mini *mini)
{
	long long	error;

	error = 0;
	if (pipe_exit(mini, error) == true)
		return (true);
	if (!mini->args[1] || !mini->args)
		return (mini->exit = 1);
	if (mini->args[2])
		return (ft_exit(mini, "too many arguments", 1, 0), true);
	else
	{
		if (check_num(mini, mini->args[1]) == -1)
			return (mini->exit = 1);
		error = ft_atoll(mini->args[1]);
		if (error >= 9223372036854775807LL)
			ft_exit(mini, "numeric arguement required", error, 0);
		while (error > 255)
			error %= 256;
		mini->errno_code = error;
	}
	if (ft_strcmp(mini->args[1], "") == 0)
		mini->errno_code = 1;
	return (mini->exit = 1);
}
