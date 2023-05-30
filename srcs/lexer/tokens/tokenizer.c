/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:28:49 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/27 18:44:15 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_toktype	get_type_array(
	const char *type_str[],
	char *word)
{
	size_t	enum_index;

	enum_index = 0;
	while (enum_index < T_ASSIGN
		&& streq(type_str[enum_index], word) == false)
		++enum_index;
	if (enum_index == T_ASSIGN)
	{
		if (is_assign(word) == true)
			return (T_ASSIGN);
		if (is_qword(word) == true)
			return (T_QGENERIC);
		else
			return (T_GENERIC);
	}
	return (enum_index);
}

static t_toktype	get_type(char *word)
{
	const char	*type_str[] = {
		LCHEVRON,
		RCHEVRON,
		DOUBLE_LCHEVRON,
		DOUBLE_RCHEVRON,
		PIPE,
		OR,
		AND,
		SEP
	};

	return (get_type_array(type_str, word));
}

static t_token	*set_token(char *word)
{
	if (word == NULL)
		return (NULL);
	return (init_token(get_type(word), word));
}

t_list	*tokenizer(t_list *words)
{
	t_list	*new_head;
	t_list	*curr;

	if (words == NULL)
		return (NULL);
	new_head = ft_lstnew(set_token(words->content));
	curr = new_head;
	add_deallocator(curr, (void (*)(void *))free_token_node);
	while (words->next != NULL && curr != NULL)
	{
		curr->next = ft_lstnew(set_token(words->next->content));
		curr = curr->next;
		add_deallocator(curr, (void (*)(void *))free_token_node);
		words = words->next;
	}
	return (new_head);
}
