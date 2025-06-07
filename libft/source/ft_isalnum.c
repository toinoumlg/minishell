/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:55:50 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/10 11:16:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks for an alphanumeric character.
// Returns: 0 if false; 1 if true.
int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
