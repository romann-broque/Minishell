/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tok_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:52:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/04 16:58:07 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_qgen_to_gen(t_token *tok)
{
	if (tok->type == T_QGENERIC)
		tok->type = T_GENERIC;
}

void	set_assign_tok(t_token *tok)
{
	if (tok->type == T_GENERIC && is_assign_tok(tok) == true)
		tok->type = T_ASSIGN;
}

void	set_simple_eq_to_gen(t_token *tok)
{
	if (tok->type == T_ASSIGN
		&& streq(tok->value, EQUAL_SIGN_STR) == true)
		tok->type = T_GENERIC;
}
