/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:06:27 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/30 15:22:29 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Once the Return value of the previous command can be retrieved
//	add a function that test if the character is '?' on line 35
//	create a func that take this number and adds it to the n_line
//	you will also have to change the get_new_line_len func to take it into account
//	remove '?' from is_special_character func

void	fill_new_line(char *line, char *n_line, char *value, size_t n_l_len)
{
	size_t	i_line;
	size_t	i_new_line;
	size_t	i_value;
	size_t	value_len;

	i_line = 0;
	i_new_line = 0;
	i_value = 0;
	if (value == NULL)
		value_len = 0;
	else
		value_len = ft_strlen(value);
	while (line[i_line] != '$')
		n_line[i_new_line++] = line[i_line++];
	i_line++;
	if (is_special_character(line[i_line]) == true)
		i_line += get_special_len(line, i_line);
	else
	{
		while (ft_isalnum(line[i_line]) == 1 || line[i_line] == '_')
			i_line++;
	}
	while (i_value < value_len)
		n_line[i_new_line++] = value[i_value++];
	while (i_new_line < n_l_len)
		n_line[i_new_line++] = line[i_line++];
	n_line[i_new_line] = '\0';
}
