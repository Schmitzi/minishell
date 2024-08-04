/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:35:26 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:09 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	result = malloc(ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char func(unsigned int i, char c)
{
    if (i % 2 == 0) 
        return ft_toupper(c);
	else
        return ft_tolower(c);
}

int main(void)
{
    char input[] = "Hello, World!";
    char *result = ft_strmapi(input, func);
	if (result != NULL)
	{
        printf("Result: %s\n", result);
        free(result);
	}
    else
        printf("Error: Memory allocation failed.\n");
    return (0);
}
*/