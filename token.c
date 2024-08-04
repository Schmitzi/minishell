/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:02:47 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 17:33:02 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_init(t_mini *mini)
{
	mini->token.i = 0;
	mini->token.j = 0;
	mini->token.start = 0;
	mini->token.isq = 0;
	mini->token.idq = 0;
	mini->token.str = (char **)malloc(sizeof(char *) * \
		(arg_formula(mini->cmds[mini->i]) + 1));
	if (mini->token.str == NULL)
		return (false);
	return (true);
}

void	toggle_quotes(t_token *token, char c)
{
	if (c == '\'' && !token->idq)
		token->isq = !token->isq;
	else if (c == '\"' && !token->isq)
		token->idq = !token->idq;
}

char	*allocate_token(char *input, int start, int end)
{
	char	*token;
	int		len;

	len = end - start;
	token = (char *)malloc(sizeof(char) * (len + 1));
	if (token == NULL)
		return (NULL);
	if (token)
	{
		ft_strncpy(token, input + start, len);
		token[len] = '\0';
	}
	return (token);
}

void	special_loop(t_token *token, char *input)
{
	if (input[token->i] == '<' || input[token->i] == '>'
		|| input[token->i] == '|')
	{
		if (token->i != token->start)
			token->str[token->j++]
				= allocate_token(input, token->start, token->i);
		token->str[token->j] = (char *)malloc(2);
		if (token->str[token->j] == NULL)
			return ;
		token->str[token->j][0] = input[token->i];
		token->str[token->j][1] = '\0';
		token->j++;
		token->start = token->i + 1;
	}
	else if (input[token->i] == ' ')
		handle_spaces(token, input);
}

int	tokenize(t_mini *mini)
{
	if (token_init(mini) == false)
		return (false);
	while (mini->cmds[mini->i][mini->token.i])
	{
		toggle_quotes(&mini->token, mini->cmds[mini->i][mini->token.i]);
		if ((mini->cmds[mini->i][mini->token.i] == ' ' || \
			mini->cmds[mini->i][mini->token.i] == '<' || \
			mini->cmds[mini->i][mini->token.i] == '>' || \
			mini->cmds[mini->i][mini->token.i] == '|') && !mini->token.isq && \
			!mini->token.idq)
		{
			if (handle_special_chars(&mini->token, mini->cmds[mini->i])
				== false)
				special_loop(&mini->token, mini->cmds[mini->i]);
		}
		mini->token.i++;
	}
	finalize_token(&mini->token, mini->cmds[mini->i]);
	if (mini->token.str == NULL)
		return (ft_exit(mini, "Bad mini->token", 2, 0),
			free(mini->token.str), false);
	mini->args = mini->token.str;
	if (mini->args == NULL)
		return (free_array(mini->token.str), false);
	return (true);
}
