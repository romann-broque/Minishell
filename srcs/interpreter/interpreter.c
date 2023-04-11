/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:19 by mat               #+#    #+#             */
/*   Updated: 2023/04/11 17:07:24 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(t_list *tokens, const char **env)
{
	t_command	*cmd_data;

	cmd_data = (t_command *)malloc(sizeof(t_command));
	if (cmd_data != NULL)
	{
		cmd_data->command = get_arg_array(tokens);
		if (cmd_data->command == NULL)
			return (NULL);
		cmd_data->env = env;
		cmd_data->fdin = STDIN_FILENO;
		cmd_data->fdout = STDOUT_FILENO;
	}
	return (cmd_data);
}

static void	skip_until_generic(t_list **tokens)
{
	t_toktype	token_type;

	token_type = get_type_from_tok((*tokens)->content);
	while (token_type != T_GENERIC && token_type != T_END)
	{
		*tokens = (*tokens)->next;
		token_type = get_type_from_tok((*tokens)->content);
	}
}

t_list	*interpreter(t_list *tokens, const char **env)
{
	t_command	*cmd_data;
	t_list		*commands;

	skip_until_generic(&tokens);
	cmd_data = init_command(tokens, env);
	commands = ft_lstnew(cmd_data);
	return (commands);
}
