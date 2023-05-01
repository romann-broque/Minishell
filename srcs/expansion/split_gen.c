/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:26:46 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/28 15:29:33 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_toklist_from_array(char **strs, const size_t size)
{
	size_t	i;
	t_list	*tokens_list;

	tokens_list = NULL;
	i = 0;
	while (i < size)
	{
		ft_lstadd_back(&tokens_list, ft_lstnew(init_token(T_GENERIC, strs[i])));
		i++;
	}
	return (tokens_list);
}

static t_list	*split_gen_tok(t_token *token)
{
	char *const		content = token->value;
	char **const	split = ft_split_set(content, SEPARATORS);
	const size_t	size = get_size_strs(split);
	t_list *const	split_lst = get_toklist_from_array(split, size);

	free_strs(split);
	return (split_lst);
}

static t_list	*dup_toknode(t_list *node)
{
	t_token *const	curr_tok = node->content;

	return (ft_lstnew(init_token(curr_tok->type, curr_tok->value)));
}

static t_list	*get_split_gen(t_list *tokens)
{
	t_list	*new;

	new = tokens;
	if (tokens != NULL)
	{
		tokens = tokens->next;
		new->next = NULL;
	}
	while (tokens != NULL)
	{
		if (get_type_from_tok(tokens->content) == T_GENERIC)
			ft_lstadd_back(&new, split_gen_tok(tokens->content));
		else
			ft_lstadd_back(&new, dup_toknode(tokens));
		tokens = tokens->next;
	}
	return (new);
}

void	split_gen(t_list **tokens)
{
	t_list	*tmp;

	if (*tokens != NULL)
	{
		tmp = (*tokens)->next;
		*tokens = get_split_gen(*tokens);
		ft_lstclear(&tmp, (void (*)(void *))free_token);
	}
}
