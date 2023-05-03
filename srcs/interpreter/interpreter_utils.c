/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:38:17 by mat               #+#    #+#             */
/*   Updated: 2023/05/03 10:10:44 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd_data)
{
	if (cmd_data != NULL)
	{
		free_strs(cmd_data->command);
		free_strs(cmd_data->env);
	}
	free(cmd_data);
}

size_t	get_word_count(t_list *tokens)
{
	t_toktype	type;
	size_t		count;

	count = 0;
	type = get_type_from_tok(tokens->content);
	while (type == T_GENERIC || type == T_ASSIGN)
	{
		tokens = tokens->next;
		type = get_type_from_tok(tokens->content);
		++count;
	}
	return (count);
}

static void	cpy_arg_lst_to_array(char ***dest, t_list *tokens)
{
	t_toktype	type;
	size_t		i;

	i = 0;
	type = get_type_from_tok(tokens->content);
	while (type == T_GENERIC || type == T_ASSIGN)
	{
		(*dest)[i] = ft_strdup(get_str_from_tok(tokens->content));
		if ((*dest)[i] == NULL)
		{
			free_strs(*dest);
			perror(MALLOC_ERROR);
			*dest = NULL;
			return ;
		}
		tokens = tokens->next;
		type = get_type_from_tok(tokens->content);
		++i;
	}
	(*dest)[i] = NULL;
}

char	**get_arg_array(t_list *tokens)
{
	const size_t	size = get_word_count(tokens);
	char			**arg_array;

	arg_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (arg_array == NULL)
	{
		perror(MALLOC_ERROR);
		return (NULL);
	}
	cpy_arg_lst_to_array(&arg_array, tokens);
	return (arg_array);
}
