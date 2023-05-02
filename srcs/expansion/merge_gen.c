/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:23:22 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/30 14:52:36 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_gen_tok(t_list *tokens)
{
	return (tokens != NULL
		&& (get_type_from_tok(tokens->content) == T_GENERIC
			|| get_type_from_tok(tokens->content) == T_QGENERIC
			|| get_type_from_tok(tokens->content) == T_ASSIGN));
}

static void	get_merge_str(t_list **tokens, char **merge_str)
{
	while (is_gen_tok((*tokens)->next) == true)
	{
		*merge_str = ft_strjoin_free(*merge_str,
				get_str_from_tok((*tokens)->next->content));
		*tokens = (*tokens)->next;
	}
}

static void	merge_gen_tok(t_list *tokens)
{
	t_list	*first_gen;
	t_list	*tmp_lst;
	char	*merge_str;

	first_gen = tokens;
	merge_str = (char *)(((t_token *)(first_gen->content))->value);
	get_merge_str(&tokens, &merge_str);
	if (merge_str != NULL)
	{
		tmp_lst = NULL;
		if (tokens != NULL)
		{
			tmp_lst = tokens->next;
			tokens->next = NULL;
		}
		((t_token *)(first_gen->content))->value = merge_str;
		ft_lstclear(&(first_gen->next), (void (*)(void *))free_token);
		first_gen->next = tmp_lst;
	}
}

void	merge_gen_lst(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (is_gen_tok(tokens) == true)
			merge_gen_tok(tokens);
		tokens = tokens->next;
	}
}
