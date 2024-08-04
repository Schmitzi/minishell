/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:37:43 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:34 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*mem1;
	const unsigned char	*mem2;

	mem1 = s1;
	mem2 = s2;
	while (n-- > 0)
	{
		if (*mem1 != *mem2)
			return (*mem1 - *mem2);
		mem1++;
		mem2++;
	}
	return (0);
}
/*
int	main(void)
{
	const void *s1 = "Hella ";
	const void *s2 = "Hell";
	int n = 5;
	printf("ft_memcmp:\n%d\n", ft_memcmp(s1, s2, n));
	printf("memcmp:\n%d\n", memcmp(s1, s2, n));
	return (0);
}
*/