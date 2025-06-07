/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:07:47 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/10 11:11:58 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Erases the data in the n bytes of the memory.
// Starting at the location pointed to by s, by writing '\0' to that area.
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	i = 0;
	if (!s)
		return ;
	uc_s = (unsigned char *)s;
	while (i < n)
	{
		uc_s[i] = 0;
		i++;
	}
	return ;
}
