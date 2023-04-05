/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:59:54 by mat               #+#    #+#             */
/*   Updated: 2023/04/05 11:03:38 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_var_charset(const char c)
{
	return (is_in_var_start_charset(c) || ft_isdigit(c));
}

char	*cut_string_at(char *str, const size_t index, const size_t del_len)
{
	return (replace_and_free(str, EMPTY_STR, index, del_len));
}

bool	is_in_var_start_charset(const char c)
{
	return (ft_isalpha(c) || c == UNDERSCORE);
}

bool	is_special_var(const char c)
{
	return (is_in_str(SPECIAL_VAR, c));
}

char	*replace_and_free(
	char *src,
	char *replace,
	size_t index,
	size_t delete_len
	)
{
	char *const	new_str = replace_str(src, replace, index, delete_len);

	free(src);
	return (new_str);
}
