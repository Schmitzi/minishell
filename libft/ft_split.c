/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:24:07 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/05/25 01:28:53 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_place(char const *s, char c, size_t n)
{
	while (s[n] != '\0' && s[n] != c)
		n++;
	return (n);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	lst = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (NULL);
	while (i < ft_count(s, c))
	{
		while (s[n] == c)
			n++;
		lst[i] = ft_substr(s, n, ft_place(s, c, n) - n);
		if (!lst[i++])
		{
			while (i > 0)
				free(lst[--i]);
			free(lst);
			return (NULL);
		}
		n = ft_place(s, c, n) + 1;
	}
	lst[i] = NULL;
	return (lst);
}

/*
int main(void)
{
    char const *s = "Old Man Duck";
    char c = ' ';
    char **result = ft_split(s, c);
	size_t	i = 0;

    if (result)
	{
        while (result[i] != NULL)
		{
            printf("%s\n", result[i]);
            free(result[i]);
			i++;
        }
        free(result);
    }
	else
	{
        printf("Memory allocation failed.\n");
	}
    return (0);
}
*/