/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:43:27 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 13:11:15 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
void func(unsigned int index, char *c)
{
    if (index % 2 == 0) 
        *c = ft_toupper((int)*c);
    else
        *c = ft_tolower((int)*c);
}

int main() {
    char s[] = "Hello, World!";
    
    printf("Before: %s\n", s);
    ft_striteri(s, func);
	printf("After: %s\n", s);

    return (0);
}
*/
