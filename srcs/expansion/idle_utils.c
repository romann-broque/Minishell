/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idle_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:13:24 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/28 16:14:42 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	idle_tok(t_token *token)
{
	if (token != NULL)
		token->type = T_IDLE;
}

static int	tok_comp(t_token *tok1, t_token *tok2)
{
	if (tok1->type == tok2->type && streq(tok1->value, tok2->value) == true)
		return (0);
	return (1);
}

void	idle_empty_var(t_list *tokens)
{
	static t_token	tok_ref = {.type = T_VAR, .value = EMPTY_STR};

	while (tokens != NULL)
	{
		if (tok_comp(tokens->content, &tok_ref) == 0)
			idle_tok(tokens->content);
		tokens = tokens->next;
	}
}

static void	unset_useless_idle(t_list *prev, t_list *curr, t_list *next)
{
	const t_toktype	prev_type = get_type_from_tok(prev->content);
	const t_toktype	curr_type = get_type_from_tok(curr->content);

	if (prev_type != T_LCHEVRON
		&& prev_type != T_RCHEVRON
		&& prev_type != T_DOUBLE_RCHEVRON
		&& curr_type == T_IDLE)
	{
		prev->next = next;
	}
}

void	rm_useless_idle(t_list *tokens)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	curr = NULL;
	while (tokens != NULL)
	{
		prev = curr;
		curr = tokens;
		next = tokens->next;
		if (prev != NULL && curr != NULL)
			unset_useless_idle(prev, curr, next);
		tokens = tokens->next;
	}
}
