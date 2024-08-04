/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:59:28 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/19 14:05:45 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	char	*new_str;
	int		len;

	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	new_str = malloc(len + 2);
	if (new_str == NULL)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	else
		new_str[0] = '\0';
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
