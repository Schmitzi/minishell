/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:52:29 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 13:51:41 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reg_expand(t_mini *mini)
{
	mini->exp.var_start = mini->exp.p;
	while (*mini->exp.p && (ft_isalnum(*mini->exp.p) || *mini->exp.p == '_'))
		mini->exp.p++;
	mini->exp.var_len = mini->exp.p - mini->exp.var_start;
	mini->exp.var_name = malloc(mini->exp.var_len + 1);
	if (!mini->exp.var_name)
		return (free(mini->exp.res), false);
	ft_strncpy(mini->exp.var_name, mini->exp.var_start, mini->exp.var_len);
	mini->exp.var_name[mini->exp.var_len] = '\0';
	mini->exp.var_value = ft_getenv(mini, mini->exp.var_name);
	free(mini->exp.var_name);
	if (mini->exp.var_value)
	{
		mini->exp.value_len = ft_strlen(mini->exp.var_value);
		ft_memcpy(mini->exp.res_ptr, mini->exp.var_value, mini->exp.value_len);
		mini->exp.res_ptr += mini->exp.value_len;
	}
	return (true);
}

// New function to handle quote state transitions
void	handle_dec_quotes(const char **p, char **res_ptr, int *isq, int *idq)
{
	if (**p == '\'' && !(*idq))
		*isq = !(*isq);
	else if (**p == '"' && !(*isq))
		*idq = !(*idq);
	**res_ptr = **p;
	(*res_ptr)++;
	(*p)++;
}

// New function to handle variable expansion
int	handle_variable_expansion(t_mini *mini)
{
	if (*(mini->exp.p + 1) == '?' || ft_isalnum(*(mini->exp.p + 1)) || \
		*(mini->exp.p + 1) == '_')
	{
		mini->exp.p++;
		if (*mini->exp.p == '?')
		{
			if (print_errno(mini) == false)
				return (false);
		}
		else
		{
			if (reg_expand(mini) == false)
				return (false);
		}
	}
	else
	{
		*mini->exp.res_ptr++ = *mini->exp.p++;
	}
	return (true);
}

// New function to copy a single character to the result buffer
void	copy_char(const char **p, char **res_ptr)
{
	**res_ptr = **p;
	(*res_ptr)++;
	(*p)++;
}

// Refactored expand_string function
char	*expand_string(t_mini *mini, char *input)
{
	char	*res;

	if (exp_init(&mini->exp, input) == false)
		return (NULL);
	while (*mini->exp.p)
		deciding(mini);
	*mini->exp.res_ptr = '\0';
	res = ft_strdup(mini->exp.res);
	if (res == NULL)
		return (free(mini->exp.res), NULL);
	if (ft_strcmp("", res) == 0)
		return (free(res), free(mini->exp.res), NULL);
	return (free(mini->exp.res), res);
}
