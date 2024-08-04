/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:08:58 by codespace         #+#    #+#             */
/*   Updated: 2024/05/25 01:32:35 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	abs_value(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static int	get_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		++len;
	while (nbr != 0)
	{
		++len;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*result;
	int		len;

	len = get_len(nbr);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (nbr < 0)
		result[0] = '-';
	else if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		--len;
		result[len] = abs_value(nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}

// int		main(void)
// {
// 	int d = INT_MIN;
// 	printf("%d =? %s\n", d, ft_itoa(d));
//	return (0);
// }