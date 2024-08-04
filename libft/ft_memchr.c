/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:09:34 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:38 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		find;

	src = s;
	find = (unsigned char ) c;
	while (n > 0)
	{
		if (*src == find)
			return ((void *)src);
		src++;
		n--;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("ft_memchr:\n%p\n", ft_memchr("Old Man Duck", 'n', 4));
	printf("memchr:\n%p\n", memchr("Old Man Duck", 'n', 4));
}
*/
