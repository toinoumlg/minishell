/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:00:53 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/10 11:18:42 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Deletes and frees the given node and every successor of that node.
// Using  the function ’del’ and free(3).
// Pointer to the list is set to NULL.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		new = current->next;
		ft_lstdelone(current, del);
		current = new;
	}
	*lst = NULL;
}
