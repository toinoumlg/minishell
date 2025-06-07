/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:17:16 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/15 08:40:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	allocate(size_t len, size_t start, size_t len_s)
{
	if (start > len_s)
		return (0);
	else if (len > len_s)
		return (len_s - start);
	else if (len_s - start < len)
		return (len_s - start);
	else
		return (len);
}

// Allocates (with malloc(3)) and returns a substring from the string 's'.
// The substring begins at index ’start’ and is of maximum size ’len’.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*sub_string;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	sub_string = malloc(sizeof(char) * allocate(len, start, len_s) + 1);
	if (!sub_string)
		return (NULL);
	i = 0;
	if (start >= len_s)
	{
		sub_string[i] = 0;
		return (sub_string);
	}
	while (i < len && s[start + i])
	{
		sub_string[i] = s[start + i];
		i++;
	}
	sub_string[i] = 0;
	return (sub_string);
}
