/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:24:35 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/18 08:39:21 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	sign = 0;
	num = 0;
	i = 0;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\v'
		|| *nptr == '\r' || *nptr == '\f')
		nptr++;
	{
		if (*nptr == '-')
			sign = 1;
		if (*nptr == '-' || *nptr == '+')
			nptr++;
		while (nptr[i] >= 48 && nptr[i] <= 57)
		{
			num = (nptr[i] - 48) + (10 * num);
			i++;
		}
		if (sign == 1)
			num = num * -1;
	}
	return (num);
}
/*
int main(void)
{
    char    *nptr = "--1237348+-++-+";
//  char    *nptr = "    --1234ab567";
    printf("ft_atoi: \n%d\n", ft_atoi(nptr));
    printf("atoi: \n%d\n", atoi(nptr));
    return (0);
}
*/