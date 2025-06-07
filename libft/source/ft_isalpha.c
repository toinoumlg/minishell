/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:28:33 by amalangu          #+#    #+#             */
/*   Updated: 2024/10/13 12:34:08 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks for an alphabetic character.
// Returns: 0 if false; 1 if true.
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
