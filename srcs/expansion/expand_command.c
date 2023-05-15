/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:02:35 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/15 10:31:20 by rbroque          ###   ########.fr       */
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

void	expand_command(t_list **tokens)
{
	ft_lstiter(*tokens, (void (*)(void *))expand);
	split_gen(tokens);
	merge_gen_lst(*tokens);
	ft_lstiter(*tokens, (void (*)(void *))set_assign_tok);
	ft_lstiter(*tokens, (void (*)(void *))set_qgen_to_gen);
	ft_lstiter(*tokens, (void (*)(void *))set_simple_eq_to_gen);
	remove_sep_tok(tokens);
}
