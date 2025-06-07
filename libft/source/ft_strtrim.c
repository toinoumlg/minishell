/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:10:37 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/15 08:43:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	start_f(const char *s1, const char *set)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (set[i])
	{
		if (s1[j] == set[i])
		{
			j++;
			i = 0;
		}
		else
			i++;
	}
	return (j);
}

int	end_f(const char *s1, const char *set, int lenght)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1[lenght - 1] == set[i])
		{
			lenght--;
			i = 0;
		}
		else
			i++;
	}
	return (lenght);
}

// Allocates and returns a copy of ’s1’
// With the characters specified in ’set’ removed
// From the beginning and the end of the string
char	*ft_strtrim(char const *s1, char const *set)
{
	int		lenght;
	int		start;
	int		end;
	char	*result;
	int		i;

	if (!s1 || !set)
		return (NULL);
	lenght = ft_strlen(s1);
	start = start_f(s1, set);
	end = end_f(s1, set, lenght);
	if (start != lenght)
		result = malloc(sizeof(char) * end - start + 1);
	else
		result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		result[i] = s1[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
