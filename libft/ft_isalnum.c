/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:32:15 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 14:08:05 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (8);
	return (0);
}
/*
int	main(void)
{
	printf("A: %c", ft_isalnum('A'));
	printf("a: %c", ft_isalnum('a'));
	printf("0: %c", ft_isalnum('0'));
	printf("{: %c", ft_isalnum(123));
	return (0);
}
*/