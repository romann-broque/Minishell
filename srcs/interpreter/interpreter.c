/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:19 by mat               #+#    #+#             */
/*   Updated: 2023/04/11 15:54:04 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_word_count(t_list *tokens)
{
	size_t	size;

	size = 0;
	while (get_type_from_tok(tokens->content) == T_GENERIC)
		size++;
	return (size);
}

char	**get_arg_array(t_list *tokens)
{
	const size_t	size = get_word_count(tokens);
	size_t			i;
	char			**arg_array;

	arg_array = malloc(sizeof(char *) * (size + 1));
	if (arg_array == NULL)
	{
		perror(MALLOC_ERROR);
		return (NULL);
	}
	i = 0;
	while (get_type_from_tok(tokens->content) == T_GENERIC)
	{
		arg_array[i] = ft_strdup(get_str_from_tok(tokens->content));
		if (arg_array[i] == NULL)
		{
			free_strs(arg_array);
			perror(MALLOC_ERROR);
			return (NULL);
		}
		i++;
	}
	arg_array[i] = NULL;
	return (arg_array);
}

void	interpret_command(t_list *tokens, t_command *cmd_data)
{
	cmd_data->command = get_arg_array(tokens);
	if (cmd_data->command == NULL)
		return ;
	cmd_data->fdin = STDIN_FILENO;
	cmd_data->fdout = STDOUT_FILENO;
	cmd_data->path = find_cmd_path(cmd_data->command[0]);
}

void	skip_until_generic(t_list **tokens)
{
	t_toktype	token_type;

	token_type = get_type_from_tok((*tokens)->content);
	while (token_type != T_GENERIC && token_type != T_END)
	{
		*tokens = (*tokens)->next;
		token_type = get_type_from_tok((*tokens)->content);
	}
}

t_list	*interpreter(t_list *tokens)
{
	t_list		*commands;
	t_command	cmd_data;

	skip_until_generic(&tokens);
	interpret_command(tokens, &cmd_data);
	commands = ft_lstnew(&cmd_data);
	return (commands);
}
