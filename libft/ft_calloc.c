/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:23:36 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:10:26 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
	{
		p = malloc(0);
		if (p == NULL)
			return (NULL);
	}
	else
	{
		p = malloc(nmemb * size);
		if (p == NULL)
			return (NULL);
		ft_memset(p, 0, nmemb * size);
	}
	return (p);
}
/*
int main(void)
{

    char	*arr = (char*)ft_calloc(2,1);
	
	printf("%s\n", arr);
	return (0);
}
*/