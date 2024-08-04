/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:02:36 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/30 17:29:52 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pre_trim(char *input, char delim)
{
	char		*ptr;
	size_t		len;
	char		*result;

	if (input == NULL)
		return (NULL);
	ptr = ft_strchr(input, delim);
	if (ptr == NULL)
		return (input);
	len = (ptr - input);
	if (len > ft_strlen(input))
		return (NULL);
	result = (char *)malloc((len + 1));
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, input, len);
	if (result == NULL)
		return (free(ptr), NULL);
	result[len] = '\0';
	return (result);
}

char	*post_trim(char *input, char delim)
{
	char	*ptr;
	char	*result;

	if (input == NULL)
		return (NULL);
	ptr = ft_strchr(input, delim);
	if (ptr == NULL)
		return (ft_strdup(""));
	result = (char *)malloc(ft_strlen(ptr + 1) + 1);
	if (result == NULL)
		return (free(ptr), NULL);
	ft_strcpy(result, ptr + 1);
	return (result);
}

char	*last_occur(char *input, char delim)
{
	char	*ptr;
	size_t	len;
	char	*result;

	if (input == NULL)
		return (NULL);
	ptr = ft_strrchr(input, delim);
	if (ptr == NULL)
		return (input);
	len = ft_strlen(ptr + 1);
	result = ft_strdup(ptr);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, ptr + 1, len + 1);
	return (result);
}

int	check_num(t_mini *mini, char *str)
{
	char	*error;
	char	*temp;

	if (str[0] == '+' || str[0] == '-')
		temp = str + 1;
	else
		temp = str;
	error = ft_itoa(ft_atoll(temp));
	if (error == NULL)
		return (false);
	if (ft_strcmp(error, temp) != 0)
	{
		ft_exit(mini, "numeric argument required", 2, 0);
		return (free(error), false);
	}
	return (free(error), true);
}

void	space_trim(char **args)
{
	int	i;
	int	len;

	i = 0;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		while (len > 0 && args[i][len - 1] == ' ')
		{
			args[i][len - 1] = '\0';
			len--;
		}
		if (ft_strcmp(args[i], "") == 0)
		{
			free(args[i]);
			args[i] = "";
		}
		i++;
	}
}
