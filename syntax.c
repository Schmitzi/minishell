/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:17:33 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:30:01 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	some_quote(char *s, int n)
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
		else if (s[i] == '\"' && res != 1)
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

static int	syntax_pip(char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == '|' && status == 0 && some_quote(str, i) == 0)
			return (false);
		else if (str[i] == '|' && status == 1 && some_quote(str, i) == 0)
			status = false;
		else if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			status = true;
		i++;
	}
	return (status);
}

static int	skip_spacy(char *s, int i)
{
	i++;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == '\0')
		return (false);
	return (true);
}

static int	syntax_red(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		while ((s[i] != '>' && s[i] != '<' && \
		s[i] != '\0') || some_quote(s, i) != 0)
			i++;
		if (s[i] != '\0' && s[i] == s[i + 1])
			i++;
		if (s[i] != '\0' && skip_spacy(s, i) == false)
			return (false);
		if (s[i] != '\0')
			i++;
	}
	return (true);
}

int	syntax_check(char *s)
{
	if (some_quote(s, ft_strlen(s)) != 0)
		return (false);
	if (syntax_pip(s) == 0)
		return (false);
	if (syntax_red(s) == 0)
		return (false);
	return (true);
}
