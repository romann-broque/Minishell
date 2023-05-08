/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:59:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/08 14:43:12 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_same_tok(t_token *tok1, t_token *tok2)
{
	return (tok1->type == tok2->type
		&& streq(tok1->value, tok2->value));
}

void	remove_sep_tok(t_list **tokens)
{
	static t_token	sep_tok = {.type = T_SEPARATOR, .value = SEP};

	ft_list_remove_if(tokens, &sep_tok,
		(bool (*)(void *, void *))is_same_tok, (void (*)(void *))free_token);
}
