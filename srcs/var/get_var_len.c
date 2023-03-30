/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:52:32 by mat               #+#    #+#             */
/*   Updated: 2023/03/30 13:51:11 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t get_special_len(char *line, ssize_t index)
{
	size_t	len;

	len = 0;
	if (line[index] == '?' || line[index] == '$')
		return (1);
	while (ft_isdigit(line[index++]) == 1)
		len++;
	return (len);
}

bool is_special_character(char c)
{
	if (c == '?' || c == '$' || ft_isdigit(c) == 1)
		return (true);
	return (false);
}

size_t	get_var_len(char *line, ssize_t index)
{
	size_t	len;

	len = 0;
	if (is_special_character(line[index]) == true)
		return (get_special_len(line, index));
	while (ft_isalnum(line[index]) == 1 || line[index] == '_')
	{
		index++;
		len++;
	}
	return (len);
}
