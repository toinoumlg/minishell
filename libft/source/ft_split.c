/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:02:28 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/07 15:50:45 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
}

int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*fill_word(char const *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

// Allocates with malloc() and returns an array of strings.
// Obtained by splitting ’s’ using ’c’ as a delimiter.
// Array is ended with a NULL pointer.
char	**ft_split(char const *s, char c)
{
	char	**split;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = fill_word(s + i, c);
			if (!split[j])
				return (free_split(split), NULL);
			while (s[i] != c && s[i])
				i++;
			j++;
		}
		else
			i++;
	}
	split[j] = 0;
	return (split);
}
