/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:20:47 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 14:14:09 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
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