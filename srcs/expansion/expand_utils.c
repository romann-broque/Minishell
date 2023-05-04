/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:59:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/04 10:57:58 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tok_comp(t_token *tok1, t_token *tok2)
{
	if (tok1->type == tok2->type && streq(tok1->value, tok2->value))
		return (0);
	return (1);
}

void	remove_sep_tok(t_list **tokens)
{
	static t_token	sep_tok = {.type = T_SEPARATOR, .value = SEP};

	ft_list_remove_if(tokens, &sep_tok, tok_comp, (void (*)(void *))free_token);
}

void	set_to_gen(t_token *token)
{
	if (token->type == T_QGENERIC
		|| token->type == T_ASSIGN)
		token->type = T_GENERIC;
}

static void	set_assign_tok(t_token *token)
{
	if (is_assign_tok(token) == true)
		token->type = T_ASSIGN;
}

void	set_assign(t_list *tokens)
{
	ft_lstiter(tokens, (void (*)(void *))set_assign_tok);
}
