/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 07:41:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/06/29 13:12:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_parse_error(char *parse_error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (!parse_error || *parse_error == '\000')
	{
		ft_putstr_fd("newline'\n", 2);
		return ;
	}
	parse_error++;
	if (*parse_error == 0 || *parse_error == '\n' || *parse_error == ' ')
		ft_putstr_fd("newline'\n", 2);
	else
	{
		ft_putchar_fd(*parse_error, 2);
		ft_putstr_fd("'\n", 2);
	}
}
