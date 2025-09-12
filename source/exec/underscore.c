/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:36:35 by amalangu          #+#    #+#             */
/*   Updated: 2025/09/12 09:36:37 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static void	change_underscore(char *value, t_envp *envp)
// {
// 	t_envp	*under_score;
// 	char	*tmp;

// 	under_score = find_existing_envp("_", envp);
// 	under_score->value = ft_strdup(value);
// 	free(under_score->line);
// 	under_score->line = ft_strjoin(under_score->name, "=");
// 	tmp = under_score->line;
// 	under_score->line = ft_strjoin(tmp, value);
// 	free(tmp);
// }

// static void	handle_underscore(t_minishell *minishell)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = minishell->cmds->args;
// 	if (!args)
// 		return ;
// 	while (args[i])
// 		i++;
// 	if (i == 1)
// 		change_underscore(minishell->cmds->program->path, minishell->envp);
// 	else if (i > 1)
// 		change_underscore(minishell->cmds->args[i - 1], minishell->envp);
// }