/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:30:09 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 14:08:10 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*c;
	size_t	i;

	c = s;
	i = 0;
	while (i < n)
		c[i++] = '\0';
}
/*
int	main(void)
{
	char test[] = "0";
	printf("Before: %s\n", test);
	bzero(test, 5);
	printf("After: %s\n", test);
	return (0);
}
*/