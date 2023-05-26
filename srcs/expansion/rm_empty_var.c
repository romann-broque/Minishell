/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_empty_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:07:13 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/26 23:11:26 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flag_tok_var(t_token *token)
{
	if (token->type == T_GENERIC
		&& token->value[0] == DOLLAR_SIGN
		&& is_in_str(token->value, DOUBLE_QUOTE) == false
		&& is_in_str(token->value, SINGLE_QUOTE) == false)
		token->type = T_VAR;
}

static void	flag_tok_gen(t_token *token)
{
	if (token->type == T_VAR)
		token->type = T_GENERIC;
}

void	flag_var(t_list *tokens)
{
	ft_lstiter(tokens, (void (*)(void *))flag_tok_var);
}

static int	tok_comp(t_token *tok1, t_token *tok2)
{
	if (tok1->type == tok2->type && streq(tok1->value, tok2->value) == true)
		return (0);
	return (1);
}

void	rm_empty_var(t_list **tokens)
{
	static t_token	tok_ref = {.type = T_VAR, .value = EMPTY_STR};

	ft_list_remove_if_without_free(tokens, &tok_ref, tok_comp);
	ft_lstiter(*tokens, (void (*)(void *))flag_tok_gen);
}
