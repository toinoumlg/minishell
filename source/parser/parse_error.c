/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 07:41:40 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/19 13:37:32 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "free_utils.h"
#include "libft.h"

void	free_parsing(t_minishell *minishell)
{
	if (minishell->tokens)
		free_tokens(minishell->tokens);
	if (minishell->read_line)
		free(minishell->read_line);
	if (minishell->envp_array)
		free_array(minishell->envp_array);
	if (minishell->env)
		free_array(minishell->env);
	minishell->read_line = NULL;
	minishell->tokens = NULL;
	minishell->envp_array = NULL;
	minishell->env = NULL;
}

void	parsing_error(char *parse_error, t_minishell *minishell)
{
	minishell->last_status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (!*parse_error)
	{
		ft_putstr_fd("newline'\n", 2);
		return (free_parsing(minishell));
	}
	parse_error++;
	if (!*parse_error || *parse_error == '\n' || *parse_error == ' ')
		ft_putstr_fd("newline'\n", 2);
	else
	{
		ft_putchar_fd(*parse_error, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (free_parsing(minishell));
}
