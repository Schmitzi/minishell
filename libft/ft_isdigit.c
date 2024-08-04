/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:17:06 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 14:14:15 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
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