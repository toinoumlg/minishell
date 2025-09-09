/* ************************************************************************** */

#include "free.h"
#include "libft.h"
#include <string.h>

void	add_string_to_token(char *start, int i, t_token *new_token,
		t_minishell *minishell)
{
	new_token->string = ft_strdup(start);
	if (!new_token->string)
	{
		free(new_token);
		exit(free_on_exit_error(minishell));
	}
	new_token->string[i] = 0;
}

t_token	*set_new_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(free_on_exit_error(minishell));
	memset(new_token, 0, sizeof(t_token));
	return (new_token);
}

t_token	*append_new_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (new_token);
}
