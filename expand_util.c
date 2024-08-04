/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:02:55 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/06/19 14:22:56 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sort(t_sort *sort, char *arg)
{
	sort->i = 0;
	sort->j = 0;
	sort->in_quotes = 0;
	sort->to_expand = false;
	sort->is_escaped = false;
	sort->len = ft_strlen(arg);
	sort->new_str = (char *)malloc(sizeof(char) * (sort->len + 1));
	if (sort->new_str == NULL)
		return (false);
	return (true);
}

void	quote_toggle(t_sort *args, char c)
{
	if ((c == '"' || c == '\'') && !args->is_escaped)
	{
		if (args->in_quotes == c)
			args->in_quotes = 0;
		else if (args->in_quotes == 0)
			args->in_quotes = c;
	}
}

void	quotes_expand(t_sort *sort, char c)
{
	if (c == '\\' && !sort->is_escaped)
		sort->is_escaped = true;
	else if ((c == '"') && !sort->is_escaped)
	{
		if (sort->in_quotes == c)
			sort->in_quotes = 0;
		else if (sort->in_quotes == 0)
			sort->in_quotes = c;
	}
	else if ((c == '\'') && !sort->is_escaped)
	{
		if (sort->in_quotes == c)
			sort->in_quotes = 0;
		else if (sort->in_quotes == 0)
			sort->in_quotes = c;
	}
	else
		sort->is_escaped = false;
}

void	process_dollar_sign(t_sort *args, char *arg)
{
	int		len;

	len = 0;
	while (arg[len] && (arg[len] != '\"' || arg[len] != '\''))
		len++;
	if (args->in_quotes == '\'')
	{
		args->new_str[args->j++] = arg[args->i];
	}
	else
	{
		args->to_expand = true;
		args->new_str[args->j++] = arg[args->i];
	}
}
