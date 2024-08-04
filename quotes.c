/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:03:58 by miturk            #+#    #+#             */
/*   Updated: 2024/07/30 17:30:49 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	my_quote(char *s, int n)
{
	int		i;
	size_t	res;

	i = 0;
	res = 0;
	while (s[i] && s[i] != '\0' && i <= n)
	{
		if (s[i] == '\'' && res != 2)
		{
			if (res == 1)
				res = 0;
			else
				res = 1;
		}
		else if (s[i] == '"' && res != 1)
		{
			if (res == 2)
				res = 0;
			else
				res = 2;
		}
		i++;
	}
	return (res);
}

int	syntax_pipe(char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == '|' && status == 0 && my_quote(str, i) == 0)
			return (false);
		else if (str[i] == '|' && status == 1 && my_quote(str, i) == 0)
			status = false;
		else if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			status = true;
		i++;
	}
	return (status);
}

static int	check_heredoc_syntax(char *arg)
{
	if ((arg[0] == '<' && arg[1] == '<' && arg[2] != '\0' \
	&& !ft_isalnum(arg[2])))
		return (false);
	else if (arg[0] == '<' && arg[1] == '<' && arg[2] == '<')
		return (false);
	return (true);
}

static int	process_found(char **args, int *i)
{
	if (args[*i] == NULL)
		return (false);
	while (args[*i] != NULL && ft_strcmp(args[*i], "") != 0 && \
		!ft_isspace(args[*i][0]))
		(*i)++;
	if (ft_strcmp(args[*i], "") == 0)
		(*i)++;
	if (args[*i] != NULL && !ft_isspace(args[*i][0]) && args[*i][0] != '>' && \
		args[*i][0] != '<')
		return (false);
	return (true);
}

int	syntax_heredoc(char **args)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (args && args[i] != NULL && in_quote(args[i]) == 0)
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			found = 1;
			i++;
		}
		else if (!check_heredoc_syntax(args[i]))
			return (false);
		if (found == 1)
		{
			if (!process_found(args, &i))
				return (false);
			found = 0;
		}
		else
			i++;
	}
	return (true);
}
