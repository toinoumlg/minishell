/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:28:41 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/07 19:07:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If c is a lowercase letter, returns its uppercase equivalent.
// Otherwise, returns c.
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
