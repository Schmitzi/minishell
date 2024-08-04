/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:37:48 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:25 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (!csrc && !cdest)
		return (NULL);
	if (cdest <= csrc || cdest >= csrc + n)
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		cdest += n - 1;
		csrc += n - 1;
		while (n--)
			*cdest-- = *csrc--;
	}
	return (dest);
}
/*
int	main(void) 
{ 
	char csrc[100] = " 1 "; 
	char cdest[100];
	ft_memmove(cdest, csrc, strlen(csrc)); 
	printf("ft_memmove\n%s\n", cdest);
	memmove(cdest, csrc, strlen(csrc));
    printf("memmove\n%s\n", cdest);
	return (0); 
}
*/
