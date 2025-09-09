/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 07:41:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/09 13:39:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "free_utils.h"
#include "libft.h"

static void	free_on_parse_error(t_minishell *minishell)
{
	if (minishell->tokens)
		free_tokens(minishell->tokens);
	if (minishell->read_line)
		free(minishell->read_line);
	if (minishell->envp_array)
		free_array(minishell->envp_array);
}

void	parsing_error(char *parse_error, t_minishell *minishell)
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
	free_on_parse_error(minishell);
	return ;
}
