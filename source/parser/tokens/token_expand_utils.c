/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/16 19:43:44 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_utils.h"
#include "free.h"
#include "libft.h"
#include "minishell.h"
#include "token_list.h"
#include <stdio.h>



void	insert_space_token(char *str, t_token *token, t_minishell *minishell)
{
	t_token	*space_token;

	space_token = malloc(sizeof(t_token));
	if (!space_token)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	space_token->string = NULL;
	space_token->type = space_expanded;
	if (token->next)
		space_token->next = token->next;
	else
		space_token->next = NULL;
	token->next = space_token;
}


void	insert_word_token(char *str, t_token *token, t_minishell *minishell,
		char *value)
{
	t_token	*word_token;
	t_token	*tmp;

	if (!value)
		return ;
	word_token = malloc(sizeof(t_token));
	word_token->next = NULL;
	tmp = token;
	if (!word_token)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	word_token->string = ft_strdup(value);
	if (!word_token->string)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	word_token->type = word_expanded;
	while (tmp->next && (tmp->next->type == word_expanded
			|| tmp->next->type == space_expanded))
		tmp = tmp->next;
	if (tmp->next)
		word_token->next = tmp->next;
	else
		word_token->next = NULL;
	tmp->next = word_token;
}



int	expand_pid(char *str, t_token *token, t_minishell *minishell)
{
	char	*pid;
	char	*tmp;
	int		size;

	pid = ft_itoa(getpid());
	if (!pid)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	size = ft_strlen(pid);
	tmp = token->string;
	token->string = ft_strjoin(tmp, pid);
	free(pid);
	free(tmp);
	str++;
	tmp = token->string;
	token->string = ft_strjoin(tmp, str);
	free(tmp);
	return (size);
}
