/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:15:43 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/30 15:36:57 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_line_len(char *line, char *var_name, char *var_value)
{
	size_t	line_len;
	size_t	var_len;
	size_t	value_len;

	line_len = ft_strlen(line);
	var_len = ft_strlen(var_name);
	var_len++;
	if (var_value == NULL)
		value_len = 0;
	else
		value_len = ft_strlen(var_value);
	return (line_len - var_len + value_len);
}

static char	*get_var_name(char *line)
{
	char	*var;
	ssize_t	i;
	size_t	var_len;

	i = index_of(line, '$');
	if (i == -1)
		return (NULL);
	i++;
	var_len = get_var_len(line, i);
	var = ft_strndup(&line[i], var_len);
	if (var == NULL)
	{
		free(line);
		perror(MALLOC_ERROR);
		return (NULL);
	}
	return (var);
}

static char	*get_new_line(char *old_line)
{
	size_t	new_line_len;
	char	*new_line;
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(old_line);
	var_value = getenv(var_name);
	new_line_len = get_new_line_len(old_line, var_name, var_value);
	new_line = malloc(sizeof(char) * new_line_len + 1);
	if (new_line == NULL)
	{
		free(var_name);
		perror(MALLOC_ERROR);
		return (NULL);
	}
	fill_new_line(old_line, new_line, var_value, new_line_len);
	free(var_name);
	return (new_line);
}

char	*expand_var(char *line)
{
	char	*new_line;
	char	*new_line_tmp;

	if (line == NULL)
		return (line);
	new_line = ft_strdup(line);
	if (new_line == NULL)
	{
		perror(MALLOC_ERROR);
		return (NULL);
	}
	while (is_in_str(new_line, '$') == true)
	{
		new_line_tmp = get_new_line(new_line);
		free(new_line);
		if (new_line_tmp == NULL)
			return (NULL);
		new_line = new_line_tmp;
	}
	return (new_line);
}
