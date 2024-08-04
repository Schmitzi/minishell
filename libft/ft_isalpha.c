/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:58:20 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 14:14:06 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
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