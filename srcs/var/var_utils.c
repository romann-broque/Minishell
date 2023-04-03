/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:59:54 by mat               #+#    #+#             */
/*   Updated: 2023/04/03 17:50:20 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_var_charset(const char c)
{
	return (ft_isalnum(c) == 1 || c == '_');
}

bool	is_in_var_start_charset(const char c)
{
	return (ft_isalpha(c) == 1 || c == '_');
}

bool	is_special_var(const char c)
{
	return (is_in_str(SPECIAL_VAR, c) == true
		|| is_in_str(SEPARATORS, c) == true);
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
