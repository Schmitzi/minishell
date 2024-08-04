/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:34:06 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 16:12:19 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}
/*
int	main(void)
{
	char arr[5] = "Hello";
	int	loop = 0;
	int	length = 5;

	printf("Before ft_memset: \n");
	while(loop < len)
	{
		printf("%c ", arr[loop]);
		loop++;
	}
	printf("\n");
	ft_memset(arr+3, 'a' , len);
	printf("After ft_memset: \n");
	loop = 0;
	while(loop < len)
    {
        printf("%c ", arr[loop]);
        loop++;
    }
	printf("\n");
	return (0);
}
*/