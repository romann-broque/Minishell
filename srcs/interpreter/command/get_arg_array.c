/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:10:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/25 15:50:56 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_word_count(t_list *tokens)
{
	t_toktype	type;
	size_t		count;

	count = 0;
	type = get_type_from_tok(tokens->content);
	while (type != T_END && type != T_PIPE)
	{
		count += (type == T_GENERIC || type == T_ASSIGN);
		tokens = tokens->next;
		type = get_type_from_tok(tokens->content);
	}
	return (count);
}

void	append_to_arg_array(t_command *cmd, t_list *tokens)
{
	char **const	dest = cmd->command;
	t_toktype		type;
	size_t			i;

	type = get_type_from_tok(tokens->content);
	if (type == T_GENERIC || type == T_ASSIGN)
	{
		i = 0;
		while (dest[i] != NULL)
			++i;
		dest[i] = ft_strdup(get_str_from_tok(tokens->content));
		if (dest[i] == NULL)
			exit_alloc();
	}
}

char	**get_arg_array(t_list *tokens)
{
	const size_t	size = get_word_count(tokens);
	char			**arg_array;

	arg_array = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (arg_array == NULL)
		exit_alloc();
	return (arg_array);
}
