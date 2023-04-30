/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:46:12 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/30 12:38:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_assign_tok_state(const char *str)
{
	return (*str != EQUAL_SIGN && is_in_str(str + 1, EQUAL_SIGN));
}

bool	is_assign_tok(t_token *token)
{
	return ((token->type == T_GENERIC || token->type == T_QGENERIC)
		&& is_assign_tok_state(token->value));
}
