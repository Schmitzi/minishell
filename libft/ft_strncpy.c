/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:08:01 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/05/01 10:30:56 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	src[] = "684582";
	char	dest[20] = {0};
	unsigned int n = 2;

	printf("Dest: %s\nSrc: %s\n", dest, src);
	ft_strncpy(dest, &src[0], n);
	printf("\nDest: %s\nSrc: %s\n", dest, src);
	return (0);
}
*/
