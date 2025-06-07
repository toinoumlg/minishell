/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:08:33 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/15 07:46:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Scans n bytes of the memory pointed to by s for the first instance of c.
// Returns a pointer to the matching byte or NULL if not found.
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c_s;
	size_t			i;
	unsigned char	c_c;

	c_s = (unsigned char *)s;
	c_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (c_s[i] == c_c)
			return ((void *)(c_s + i));
		i++;
	}
	return (NULL);
}
