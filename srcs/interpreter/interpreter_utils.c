/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:38:17 by mat               #+#    #+#             */
/*   Updated: 2023/04/12 14:09:18 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd_data)
{
	if (cmd_data != NULL)
		free_strs(cmd_data->command);
	free(cmd_data);
}

size_t	get_word_count(t_list *tokens)
{
	size_t	count;

	count = 0;
	while (get_type_from_tok(tokens->content) == T_GENERIC)
	{
		tokens = tokens->next;
		++count;
	}
	return (count);
}

static void	cpy_arg_lst_to_array(char ***dest, t_list *tokens)
{
	size_t	i;

	i = 0;
	while (get_type_from_tok(tokens->content) == T_GENERIC)
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

// check : is_built-in or is_slash_name ?

char	*find_cmd_path(const char *cmd_name)
{
	(void)cmd_name;
	return (NULL);
}
