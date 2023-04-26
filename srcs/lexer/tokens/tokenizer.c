/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:28:49 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/20 15:02:45 by mat              ###   ########.fr       */
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
	return (ft_lstmap(words,
			(void *(*)(void *))set_token, (void (*)(void *))free_token));
}
