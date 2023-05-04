/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:23:22 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/04 16:56:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_merge_tok(t_list *tokens)
{
	t_toktype	type;

	if (tokens != NULL)
	{
		type = get_type_from_tok(tokens->content);
		return (type == T_GENERIC || type == T_QGENERIC || type == T_ASSIGN);
	}
	return (false);
}

static void	get_merge_str(t_list **tokens, char **merge_str)
{
	while (is_merge_tok((*tokens)->next) == true)
	{
		*merge_str = ft_strjoin_free(*merge_str,
				get_str_from_tok((*tokens)->next->content));
		*tokens = (*tokens)->next;
	}
}

static void	merge_gen_tok(t_list *tokens)
{
	t_list *const	first_gen = tokens;
	t_list			*tmp_lst;
	char			*merge_str;

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
	t_token	*tok;

	while (tokens != NULL)
	{
		if (is_merge_tok(tokens) == true)
		{
			merge_gen_tok(tokens);
			tok = tokens->content;
			if (tok->type == T_ASSIGN)
				tok->type = T_GENERIC;
		}
		tokens = tokens->next;
	}
}
