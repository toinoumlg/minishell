/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:34:14 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/15 17:48:09 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envp_utils.h"
#include "minishell.h"
#include "free.h"

int	expand_last_value(char *str, t_token *token, t_minishell *minishell)
{
	char	*nbr_str;
	char	*tmp;
	int		size;

	nbr_str = ft_itoa(minishell->last_status);
	if (!nbr_str)
	{
		free(str);
		exit_perror(minishell, "malloc");
	}
	size = ft_strlen(nbr_str);
	tmp = token->string;
	token->string = ft_strjoin(tmp, nbr_str);
	free(nbr_str);
	free(tmp);
	str++;
	tmp = token->string;
	token->string = ft_strjoin(tmp, str);
	free(tmp);
	return (size);
}

int	expand_env(char *str, t_token *token, t_minishell *minishell)
{
	t_envp	*expand;
	int		i;
	char	*tmp;
	char	c;
	int		size;

	i = 0;
	while (str[i] && str[i] != '$' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	c = str[i];
	str[i] = 0;
	expand = find_existing_envp(str, minishell->envp);
	str[i] = c;
	if (expand)
	{
		tmp = token->string;
		size = ft_strlen(expand->value) - 1;
		token->string = ft_strjoin(tmp, expand->value);
		free(tmp);
		tmp = token->string;
		token->string = ft_strjoin(tmp, str + i);
		free(tmp);
	}
	else
	{
		tmp = token->string;
		token->string = ft_strjoin(tmp, str + i);
		free(tmp);
		size = -1;
	}
	return (size);
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
