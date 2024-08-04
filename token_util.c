/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:54:34 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 14:12:07 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_chars(t_token *token, char *input)
{
	if ((input[token->i] == '<' && input[token->i + 1] == '<') || \
		(input[token->i] == '>' && input[token->i + 1] == '>'))
	{
		if (token->i != token->start)
			token->str[token->j++]
				= allocate_token(input, token->start, token->i + 2);
		else
		{
			token->str[token->j] = (char *)malloc(sizeof(char) * 3);
			if (token->str[token->j] == NULL)
				return (false);
			token->str[token->j][0] = input[token->i];
			token->str[token->j][1] = input[token->i + 1];
			token->str[token->j][2] = '\0';
			token->j++;
		}
		token->start = token->i + 2;
		token->i++;
		return (true);
	}
	return (false);
}

void	handle_spaces(t_token *token, char *input)
{
	while (input[token->i] == ' ' && input[token->i + 1] == ' ')
		token->i++;
	if (token->i != token->start)
		token->str[token->j++] = allocate_token(input, token->start, token->i);
	token->start = token->i + 1;
}

void	finalize_token(t_token *token, char *input)
{
	if (token->i != token->start)
	{
		token->str[token->j] = allocate_token(input, token->start, token->i);
		token->j++;
	}
	token->str[token->j] = NULL;
}

void	ft_free(char *str)
{
	if (!str)
		return ;
	if (str && ft_strcmp(str, "") == 0)
		free(str);
	else if (str != NULL)
		free(str);
}

int	re_arg_check(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->args[0][i])
	{
		if (mini->args[0][i] == ' ')
			i++;
		else
			break ;
		if (mini->args[0][i] == '\0')
			return (false);
	}
	i = 0;
	if (ft_strcmp(mini->args[0], "") != 0 && \
		builtin_check(mini->args[0]) == false && \
		white_check(mini->args) == false && \
		(mini->args[0][0] != '/' || mini->args[0][0] != '.'))
		return (true);
	return (false);
}
