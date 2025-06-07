/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:18:42 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/15 07:47:35 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Compares the first n bytes of the memory areas s1 and s2.
// Returns: 0 if s1 == s2 || n = 0; negative if s1 < s2; positive if s1 > s2.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	i = 0;
	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (c_s1[i] == c_s2[i] && i < n - 1)
		i++;
	return (c_s1[i] - c_s2[i]);
}
