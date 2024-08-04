/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:21:08 by miturk            #+#    #+#             */
/*   Updated: 2024/07/19 16:21:37 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skiping(char *str, int *i)
{
	while (str[*i] != ' ' && str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '|' && str[*i] != '\0')
		(*i)++;
}

static void	small_skip(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

static	void	skip_quotes(char *str, int *i)
{
	char	quote_type;

	quote_type = str[*i];
	(*i)++;
	while (str[*i] != quote_type && str[*i] != '\0')
		(*i)++;
	if (str[*i] != '\0')
		(*i)++;
}

static void	skip_quotes2(char *str, int *i, int *arg_count)
{
	while (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		(*arg_count)++;
		(*i)++;
		while (str[*i] == ' ')
			(*i)++;
	}
}

int	arg_formula(char *str)
{
	int		i;
	int		arg_count;

	i = 0;
	arg_count = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		small_skip(str, &i);
		if (str[i] == '\0')
			break ;
		arg_count++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			skip_quotes(str, &i);
			continue ;
		}
		else
			skiping(str, &i);
		skip_quotes2(str, &i, &arg_count);
	}
	return (arg_count);
}
