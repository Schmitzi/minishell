/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                  :+:      :+:    :+:      */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:49:42 by mgeiger-          #+#    #+#             */
/*   Updated: 2023/09/16 18:56:35 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	if (del == NULL)
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		ptr = *lst;
		*lst = ptr->next;
		free(ptr);
	}
	*lst = NULL;
}
