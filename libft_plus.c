/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:35:49 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 18:24:57 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *destination, const char *source, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	while (i <= num)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	in_quote(char *s)
{
	int	n;

	if (!s)
		return (0);
	n = (ft_strlen(s) - 1);
	if (n < 0)
		return (1);
	if (s[0] == '\'' && s[n] == '\'')
		return (1);
	else if ((s[0] != '\'' && s[n] == '\'') || (s[0] == '\'' && s[n] != '\''))
		return (2);
	else if ((s[0] != '\"' && s[n] == '\"') || (s[0] == '\"' && s[n] != '\"'))
		return (2);
	else if (s[0] == '\"' && s[n] == '\"')
		return (3);
	return (0);
}

int	syntax_redir(t_mini *mini, char **args)
{
	int	i;

	(void)mini;
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], ">") == 0)
		{
			i++;
			if (args[i] == NULL)
				return (false);
		}
		else if (args[i][0] == '<' && args[i][1] == '<' && args[i][2] == '<')
			return (false);
		while (args[i] != NULL)
			i++;
	}
	return (true);
}

int	edit_tool(t_mini *mini, char *key, char *value, int i)
{
	char	*temp2;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (temp == NULL)
		return (false);
	if (ft_strcmp(value, "") != 0)
		temp2 = ft_strjoin(temp, value);
	else
		temp2 = ft_strdup(temp);
	if (temp2 == NULL)
		return (free(temp), false);
	free(temp);
	if (getenv("OLDPWD") != NULL)
		free(mini->env[i]);
	mini->env[i] = ft_strdup(temp2);
	if (mini->env[i] == NULL)
		return (free(temp2), false);
	free(temp2);
	return (true);
}
