/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:52:29 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 13:51:41 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_init(t_exp *exp, char *input)
{
	exp->p = input;
	if (exp->p == NULL)
		return (false);
	exp->res = malloc(1024);
	if (!exp->res)
		return (false);
	exp->res_ptr = exp->res;
	return (true);
}

int	should_expand(char *str)
{
	int	isq;
	int	idq;

	idq = false;
	isq = false;
	while (*str)
	{
		if (*str == '\'' && !idq)
			isq = !isq;
		else if (*str == '"' && !isq)
			idq = !idq;
		else if (*str == '$' && !isq)
		{
			if (*(str + 1) == '?' || ft_isalnum(*(str + 1)) || \
				*(str + 1) == '_')
				return (true);
		}
		str++;
	}
	return (false);
}

int	print_errno(t_mini *mini)
{
	char	*errno_str;

	errno_str = ft_itoa(mini->errno_code);
	if (errno_str == NULL)
		return (false);
	mini->exp.value_len = ft_strlen(errno_str);
	ft_memcpy(mini->exp.res_ptr, errno_str, mini->exp.value_len);
	mini->exp.res_ptr += mini->exp.value_len;
	mini->exp.p++;
	free(errno_str);
	return (true);
}

int	deciding(t_mini *mini)
{
	int	isq;
	int	idq;

	isq = 0;
	idq = 0;
	if ((*mini->exp.p == '\'' && !idq) || (*mini->exp.p == '"' && !isq))
		handle_dec_quotes((const char **)&mini->exp.p, \
			&mini->exp.res_ptr, &isq, &idq);
	else if (*mini->exp.p == '$' && !isq && *(mini->exp.p + 1))
	{
		if (handle_variable_expansion(mini) == false)
			return (free(mini->exp.res), false);
	}
	else
		copy_char((const char **)&mini->exp.p, &mini->exp.res_ptr);
	return (true);
}
