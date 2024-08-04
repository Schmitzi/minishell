/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:23:22 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:10:39 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (!n || !s1 || !s2)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return ((int)(str1[i] - str2[i]));
}
/*
int main(void)
{
	char	*s1 = "11345";
	char	*s2 = "11345";
	size_t	n = 1;
	int	res = ft_strncmp(s1, s2, n);

	if (res == 0)
		printf("Strings are the same to %zu characters\n", n);
	if (res >= 1)
		printf("s1 is higher than s2 to %zu characters\n", n);
	if (res <= -1)
		printf("s1 is less than s2 to %zu characters\n", n);
	return (0);
}
*/
