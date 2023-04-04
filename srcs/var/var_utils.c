/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:59:54 by mat               #+#    #+#             */
/*   Updated: 2023/04/04 10:51:46 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_var_charset(const char c)
{
	return (is_in_var_start_charset(c) || ft_isdigit(c));
}

bool	is_in_var_start_charset(const char c)
{
	return (ft_isalpha(c) || c == UNDERSCORE);
}

bool	is_special_var(const char c)
{
	return (is_in_str(SPECIAL_VAR, c) || is_in_str(SEPARATORS, c));
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
