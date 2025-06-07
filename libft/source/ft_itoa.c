/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:43:56 by amalangu          #+#    #+#             */
/*   Updated: 2024/11/10 11:17:10 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	digit_nbr(long int n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		i++;
		n /= 10;
	}
	if (n < 0)
		i++;
	return (i + 1);
}

char	*is_positive(char *nb, long int n, int i)
{
	char	c;

	while (i >= 0)
	{
		c = n % 10 + '0';
		nb[i] = c;
		n /= 10;
		i--;
	}
	return (nb);
}

char	*is_negative(char *nb, long int n, int i)
{
	char	c;

	nb[0] = '-';
	while (i > 0)
	{
		c = n % 10 + '0';
		nb[i] = c;
		n /= 10;
		i--;
	}
	return (nb);
}

// Allocates with malloc() and returns a string.
// Representing the integer received as an argument.
char	*ft_itoa(int n)
{
	char	*nb;
	int		size;
	long	l_n;

	l_n = (long)n;
	size = digit_nbr(n);
	nb = malloc(sizeof(char) * size + 1);
	if (!nb)
		return (NULL);
	if (n < 0)
		is_negative(nb, -l_n, size - 1);
	else
		is_positive(nb, l_n, size - 1);
	nb[size] = 0;
	return (nb);
}
