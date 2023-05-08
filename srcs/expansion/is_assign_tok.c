/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assign_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:46:12 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 12:02:09 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assign_tok_state(const char *str)
{
	const ssize_t	eq_index = index_of(str, EQUAL_SIGN);
	ssize_t			i;
	bool			is_assign;

	i = 0;
	is_assign = false;
	if (eq_index > 0 && is_in_var_start_charset(str[i]) == true)
	{
		++i;
		while (is_in_var_charset(str[i]) == true)
			++i;
		is_assign = (i == eq_index);
	}
	return (is_assign);
}

bool	is_assign_tok(t_token *token)
{
	return ((token->type == T_GENERIC || token->type == T_QGENERIC)
		&& is_assign_tok_state(token->value));
}
