/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:59:15 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/07 12:17:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks whether c fits into the ASCII character set.
// Returns: 0 if false; 1 if true.
int	ft_isascii(int c)
{
	if (c >= 0 && c < 128)
		return (1);
	return (0);
}
