/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:28:49 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 14:13:19 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_toktype	get_type_array(
	const char type_str[][MAX_LEN_TYPE + 1],
	char *word)
{
	size_t	i;

	i = 0;
	while (i < TYPE_COUNT - 1 && streq(type_str[i], word) == false)
		++i;
	if (i == TYPE_COUNT - 1)
		return (T_WORD);
	return (i);
}

static t_toktype	get_type(char *word)
{
	const char	type_str[][MAX_LEN_TYPE + 1] = {
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

static t_token	*get_token(char *word)
{
	if (word == NULL)
		return (NULL);
	return (init_token(get_type(word), word));
}

t_list	*tokenizer(t_list *words)
{
	return (ft_lstmap(words,
			(void *(*)(void *))get_token, (void (*)(void *))free_token));
}
