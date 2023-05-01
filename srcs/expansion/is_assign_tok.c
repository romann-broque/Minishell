/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assign_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:46:12 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/01 10:09:50 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_assign_tok_state(const char *str)
{
	const ssize_t	eq_offset = index_of(str, EQUAL_SIGN);
	ssize_t			i;
	bool			is_assign;

	i = 0;
	is_assign = false;
	if (eq_offset > 0 && is_in_var_start_charset(str[i]) == true)
	{
		++i;
		while (is_in_var_charset(str[i]) == true)
			++i;
		is_assign = (i == eq_offset);
	}
	return (is_assign);
}

bool	is_assign_tok(t_token *token)
{
	return ((token->type == T_GENERIC || token->type == T_QGENERIC)
		&& is_assign_tok_state(token->value));
}
