/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:02:35 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 21:35:48 by rbroque          ###   ########.fr       */
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
	flag_var(*tokens);
	merge_gen_lst(*tokens);
	ft_lstiter(*tokens, (void (*)(void *))expand);
	rm_empty_var(*tokens);
	split_gen(tokens);
	merge_gen_lst_assign(*tokens);
	ft_lstiter(*tokens, (void (*)(void *))set_assign_tok);
	ft_lstiter(*tokens, (void (*)(void *))set_qgen_to_gen);
	ft_lstiter(*tokens, (void (*)(void *))set_simple_eq_to_gen);
	remove_sep_tok(tokens);
	rm_useless_idle(*tokens);
}
