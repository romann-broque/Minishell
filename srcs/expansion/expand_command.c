/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:02:35 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/27 23:18:00 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(t_token *token)
{
	char	*tmp;

	if (token != NULL)
	{
		tmp = token->value;
		if (tmp != NULL)
			token->value = expand_var(tmp);
		free(tmp);
	}
}

static int	tok_comp(t_token *tok1, t_token *tok2)
{
	if (tok1->type == tok2->type && streq(tok1->value, tok2->value))
		return (0);
	return (1);
}

static void	remove_sep_tok(t_list **tokens)
{
	static t_token	sep_tok = {.type = T_SEPARATOR, .value = SEP};

	ft_list_remove_if(tokens, &sep_tok, tok_comp, (void (*)(void *))free_token);
}

static void	set_to_gen(t_token *token)
{
	if (token->type == T_DGENERIC)
		token->type = T_GENERIC;
}

void	expand_command(t_list **tokens)
{
	remove_sep_tok(tokens);
	ft_lstiter(*tokens, (void (*)(void *))expand);
	ft_lstiter(*tokens, (void (*)(void *))set_to_gen);
}
