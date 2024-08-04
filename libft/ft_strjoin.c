/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:03:00 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/05/23 12:07:49 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str3;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	k = 0;
// 	str3 = (char *)malloc(i + j + 1);
// 	if (str3 == NULL)
// 		return (NULL); //free(s2),
// 	while (k < i)
// 	{
// 		str3[k] = s1[k];
// 		k++;
// 	}
// 	while (k < (i + j))
// 	{
// 		str3[k] = s2[k - i];
// 		k++;
// 	}
// 	str3[k] = '\0';
// 	str3[k] = '\0';
// 	//free(s1);
// 	return (str3);
// }
/*
int	main(void)
{
	char const *s1 = "Hello ";
	char const *s2 = "World!";
	printf("Joined string:\n%s\n", ft_strjoin(s1, s2));
	return (0);
}
*/