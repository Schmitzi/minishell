/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:37:35 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:06 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	cc;

	i = ft_strlen(s);
	cc = (unsigned char) c;
	if (cc == '\0')
		return ((char *)&s[i]);
	if (!*s && c == 0)
		return (NULL);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int main(void)
{
	const char *s;
	int i = 0;
	scanf("%s", &s[i]);
	int	c = 'o';
	printf("Output: %s\n", ft_strrchr(s, c));
	return (0);
}
*/