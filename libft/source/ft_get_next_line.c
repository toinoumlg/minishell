/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:02:09 by amalangu          #+#    #+#             */
/*   Updated: 2025/01/21 01:19:00 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*new_stock(char *full_string_with_nl)
{
	char	*new_stock;
	int		i;

	i = 0;
	if (ft_strlen(full_string_with_nl) < 1)
		return (NULL);
	while (full_string_with_nl[i] != '\n' && full_string_with_nl[i] != '\0')
		i++;
	if (full_string_with_nl[i] == '\0')
		return (NULL);
	i++;
	new_stock = ft_strdup(full_string_with_nl + i);
	if (ft_strlen(new_stock) == 0)
	{
		free(new_stock);
		return (NULL);
	}
	return (new_stock);
}

char	*get_string_with_lb(char *full_string_with_nl)
{
	int		i;
	int		lenght;
	char	*string_with_lb;

	i = 0;
	lenght = 0;
	while (full_string_with_nl[lenght] != '\n'
		&& full_string_with_nl[lenght] != '\0')
		lenght++;
	lenght++;
	string_with_lb = ft_calloc(sizeof(char), (lenght + 1));
	if (!string_with_lb)
		return (NULL);
	while (i < lenght)
	{
		string_with_lb[i] = full_string_with_nl[i];
		i++;
	}
	return (string_with_lb);
}

char	*stop_on_next_line(int fd)
{
	char	*read_string;
	char	*full_line;
	char	*tmp;
	int		read_size;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	read_size = BUFFER_SIZE;
	full_line = ft_calloc(sizeof(char), 1);
	while (read_size == BUFFER_SIZE)
	{
		read_string = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		read_size = read(fd, read_string, BUFFER_SIZE);
		tmp = full_line;
		full_line = ft_strjoin(tmp, read_string);
		free(tmp);
		free(read_string);
		if (ft_strchr(full_line, '\n') != 0)
			return (full_line);
	}
	return (full_line);
}

char	*join_with_stock(char *tmp, char *stock)
{
	char	*gnl;

	gnl = ft_strjoin(stock, tmp);
	free(tmp);
	free(stock);
	return (gnl);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*gnl_string;
	char		*full_string_with_nl;
	char		*tmp;

	if (ft_strchr(stock, '\n'))
	{
		gnl_string = get_string_with_lb(stock);
		tmp = stock;
		stock = new_stock(tmp);
		free(tmp);
		return (gnl_string);
	}
	full_string_with_nl = stop_on_next_line(fd);
	if (ft_strlen(full_string_with_nl) == 0 && ft_strlen(stock) == 0)
		return (free(full_string_with_nl), NULL);
	gnl_string = get_string_with_lb(full_string_with_nl);
	if (stock)
		gnl_string = join_with_stock((tmp = gnl_string), stock);
	stock = new_stock(full_string_with_nl);
	free(full_string_with_nl);
	return (gnl_string);
}
