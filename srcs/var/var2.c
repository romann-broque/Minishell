/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:06:27 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/28 19:28:47 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_new_line(char *line, char *n_line, char *value, size_t n_l_len)
{
	size_t	i_line;
	size_t	i_new_line;
	size_t	i_value;
	size_t	value_len;

	i_line = 0;
	i_new_line = 0;
	i_value = 0;
	value_len = ft_strlen(value);
	while (line[i_line] != '$')
		n_line[i_new_line++] = line[i_line++];
	i_line++;
	while (line[i_line] != ' ')
		i_line++;
	while (i_value < value_len)
		n_line[i_new_line++] = value[i_value++];
	while (i_new_line < n_l_len)
		n_line[i_new_line++] = line[i_line++];
	n_line[i_new_line] = '\0';
}
