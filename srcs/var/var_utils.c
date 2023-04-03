/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:59:54 by mat               #+#    #+#             */
/*   Updated: 2023/04/03 14:08:57 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_var_charset(char c)
{
	if (ft_isalnum((int)c) == 1 || c == '_')
		return (true);
	return (false);
}

bool	is_special_var(char c)
{
	if (c == '?' || c == '0' || c == '\0')
		return (true);
	else if (is_in_str(SEPARATORS, c) == 1)
		return (true);
	return (false);
}

char	*replace_and_free(
	char *src,
	char *replace,
	size_t index,
	size_t delete_len
	)
{
	char	*new_str;

	new_str = replace_str(src, replace, index, delete_len);
	free(src);
	return (new_str);
}
