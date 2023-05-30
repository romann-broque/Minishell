/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_empty_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:07:13 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/28 16:14:48 by rbroque          ###   ########.fr       */
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

void	rm_empty_var(t_list *tokens)
{
	idle_empty_var(tokens);
	ft_lstiter(tokens, (void (*)(void *))flag_tok_gen);
}
