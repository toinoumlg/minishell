/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:01:42 by amalangu          #+#    #+#             */
/*   Updated: 2024/10/13 12:35:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks for any printable character including space.
// Returns: 0 if false; 1 if true.
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
