/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:45:14 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:28 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	i;

	if (src == NULL && dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int main(void) 
{ 
	char csrc[5] = "hello"; 
	char cdest[5];
	size_t	n = 4;
	ft_memcpy(cdest, csrc, n); 
	printf("Before: %s\n", cdest); 
	return (0); 
}
*/
