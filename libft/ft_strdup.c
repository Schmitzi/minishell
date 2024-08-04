/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:53:30 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/05/28 14:58:36 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[len])
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int main(void)
{
    char    *dup;

    dup = ft_strdup("Hello");
    printf("%s\n", dup);
    return (0);
}
*/
