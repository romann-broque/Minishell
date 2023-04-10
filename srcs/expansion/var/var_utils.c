/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:59:54 by mat               #+#    #+#             */
/*   Updated: 2023/04/10 16:02:58 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_var_charset(const char c)
{
	return (is_in_var_start_charset(c) || ft_isdigit(c));
}

char	*cut_string_at(char *str, const size_t index, const size_t del_len)
{
	return (replace_str_free(str, EMPTY_STR, index, del_len));
}

bool	is_in_var_start_charset(const char c)
{
	return (ft_isalpha(c) || c == UNDERSCORE);
}

bool	is_special_var(const char c)
{
	return (is_in_str(SPECIAL_VAR, c));
}

void	delete_quote(t_vmachine *const machine)
{
	machine->line = cut_string_at(machine->line, machine->index, 1);
}
