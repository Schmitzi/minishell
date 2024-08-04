/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:12:32 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:13 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dst == NULL && size == 0)
		return (0);
	while (dst[i] != '\0')
		i++;
	if (size <= i)
	{
		while (src[j] != '\0')
			j++;
		return (size + j);
	}
	while (size > 0 && i < size -1 && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	while (src[j++])
		i++;
	return (i);
}
/*
int main(void)
{
    char destination[20] = "Hello, ";
    const char *source = "world!";
    size_t size = 20;

    size_t result = ft_strlcat(destination, source, size);

    printf("Result: %zu\n", result);
    printf("Concatenated String: %s\n", destination);

    return (0);
}
*/