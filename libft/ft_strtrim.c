/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:49:05 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/05/25 01:25:11 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	n;
	char	*trimmed_str;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	n = ft_strlen(s1) - 1;
	if (!*s1)
		return (ft_strdup(""));
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	while (n > i && ft_strchr(set, s1[n]) != NULL)
		n--;
	trimmed_str = ft_substr(s1, i, n - i + 1);
	if (!trimmed_str)
		return (NULL);
	free(s1);
	return (trimmed_str);
}

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	i;
// 	size_t	n;

// 	i = 0;
// 	if (s1 == NULL || set == NULL)
// 		return (NULL);
// 	n = ft_strlen(s1) - 1;
// 	if (!*s1)
// 		return (ft_strdup(""));
// 	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
// 		i++;
// 	if (s1[i] == '\0')
// 		return (ft_strdup(""));
// 	while (n > i && ft_strchr(set, s1[n]) != NULL)
// 		n--;
// 	return (ft_substr(s1, i, n - i + 1));
// }

/*
int main(void)
{
    char const *s1 = "\t\nHello\n\t";
    char const *set = "\t\n";
    if (s1 == NULL)
        printf("Input is NULL\n");
    else
	{
		printf("Before: \"%s\"\n", s1);
        printf("After: \"%s\"\n", ft_strtrim(s1, set));
	}
    return (0);
}
*/
