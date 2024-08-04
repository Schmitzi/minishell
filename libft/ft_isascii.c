/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:36:27 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:43 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c = 192;
	printf("ft_isascii\n%d\n", ft_isascii(c));
	printf("isascii\n%d\n", isascii(c));
	return (0);
}
*/
