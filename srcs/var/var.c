/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:15:43 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/29 10:06:03 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_var_len(char *dollar_ptr)
{
	size_t	i;

	i = 0;
	while (dollar_ptr[i] != ' ')
		i++;
	return (i);
}

static int	get_new_line_len(char *line, char *var_name, char *var_value)
{
	size_t	line_len;
	size_t	var_len;
	size_t	value_len;

	line_len = ft_strlen(line);
	var_len = ft_strlen(var_name);
	value_len = ft_strlen(var_value);
	return (line_len - var_len + value_len - 1);
}

//Question : Do we make an exit message specific for malloc faillure ?

static char	*get_var_name(char *line)
{
	char	*dollar_ptr;
	char	*var;
	size_t	var_len;
	size_t	i;

	dollar_ptr = ft_strrchr(line, '$');
	if (dollar_ptr == NULL)
		return (NULL);
	var_len = get_var_len(dollar_ptr);
	var = malloc(sizeof(char) * var_len + 1);
	if (var == NULL)
	{
		free(line);
		exit_shell(EXIT_FAILURE);
	}
	i = 0;
	while (dollar_ptr[i + 1] != ' ')
	{
		var[i] = dollar_ptr[i + 1];
		i++;
	}
	var[i] = '\0';
	return (var);
}

static char	*get_new_line(char *line)
{
	size_t	new_line_len;
	char	*new_line;
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(line);
	var_value = getenv(var_name);
	if (var_value == NULL)
	{
		ft_dprintf(2, "Variable %s not found\n", var_name);
		return (NULL);
	}
	new_line_len = get_new_line_len(line, var_name, var_value);
	new_line = malloc(sizeof(char) * new_line_len + 1);
	if (new_line == NULL)
	{
		free(line);
		free(var_name);
		free(var_value);
		exit_shell(EXIT_FAILURE);
	}
	fill_new_line(line, new_line, var_value, new_line_len);
	free(var_name);
	return (new_line);
}

char	*expand_var(char *line)
{
	char	*new_line;
	char	*new_line_tmp;

	if (line == NULL)
		return (line);
	new_line = line;
	if (ft_strchr(line, '$') != NULL)
	{
		new_line = get_new_line(line);
		if (new_line == NULL)
			return (line);
	}
	printf("coucou\n");
	while (ft_strchr(new_line, '$') != NULL)
	{
		new_line_tmp = get_new_line(new_line);
		free(new_line);
		if (new_line_tmp == NULL)
			return (NULL);
		new_line = new_line_tmp;
	}
	return (new_line);
}
