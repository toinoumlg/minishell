/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:56:34 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/26 11:03:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Applies 'f' to each character of the string s.
// Passing its index as the first argument.
// New string is created using malloc().
// Collect the results from the successive applications of f.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*f_str;

	if (!s || !f)
		return (NULL);
	i = 0;
	f_str = ft_strdup(s);
	if (!f_str)
		return (NULL);
	while (s[i])
	{
		f_str[i] = (*f)(i, f_str[i]);
		i++;
	}
	f_str[i] = 0;
	return (f_str);
}
