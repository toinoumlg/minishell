/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:13:10 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/10 11:14:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Allocates memory for an array of nmemb elements of size bytes each.
// Returns a pointer to the allocated memory.  The memory is set to zero.
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*_calloc;
	size_t			total;

	total = nmemb * size;
	if (size && nmemb != total / size)
		return (NULL);
	_calloc = malloc(total);
	if (!_calloc)
		return (NULL);
	if (!_calloc)
		return (NULL);
	ft_bzero(_calloc, total);
	return (_calloc);
}
