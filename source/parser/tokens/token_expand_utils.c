/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/11 17:36:38 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	return (0);
}

int	strjoin_inplace(char **dst, const char *src)
{
	char	*tmp;

	tmp = *dst;
	if (!*dst && src)
	{
		*dst = ft_strdup(src);
		if (!*dst)
			return (1);
	}
	else if (*dst && src)
	{
		*dst = ft_strjoin(tmp, src);
		if (!*dst)
			return (1);
	}
	free(tmp);
	return (0);
}
