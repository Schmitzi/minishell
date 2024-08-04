/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:47:43 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/05/25 01:27:43 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s != '\0')
// 	{
// 		if (*s++ == (char)c)
// 			return ((char *)--s);
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s++ == (char)c)
			return ((char *)--s);
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
int	main (void)
{
//	const char	*s = "0x5581ba7ac0a6";
	const char	*s = "Hello";
	int			c = 'e';
	ft_strchr(s, c);
	return (0);
}
*/
