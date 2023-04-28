/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:23:22 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/28 11:30:31 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_gen_tok(t_list *tokens)
{
	return (tokens != NULL
		&& (get_type_from_tok(tokens->content) == T_GENERIC
			|| get_type_from_tok(tokens->content) == T_DGENERIC));
}

static void	merge_gen_tok(t_list *tokens)
{
	t_list	*start;
	t_list	*tmp_lst;
	char	*merge_str;

	start = tokens;
	merge_str = (char *)(((t_token *)(start->content))->value);
	while (is_gen_tok(tokens->next) == true)
	{
		merge_str = ft_strjoin_free(merge_str,
				get_str_from_tok(tokens->next->content));
		tokens = tokens->next;
	}
	if (merge_str != NULL)
	{
		tmp_lst = NULL;
		if (tokens != NULL)
		{
			tmp_lst = tokens->next;
			tokens->next = NULL;
		}
		((t_token *)(start->content))->value = merge_str;
		ft_lstclear(&(start->next), (void (*)(void *))free_token);
		start->next = tmp_lst;
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
