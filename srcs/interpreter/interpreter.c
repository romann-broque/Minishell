/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:19 by mat               #+#    #+#             */
/*   Updated: 2023/04/20 14:14:52 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*init_command(t_list *tokens, char **env)
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

// NOTES
//For the MVE with redirections and PIPES :
//		We will have to pass into argument of init_command the type of the token
//		following the command so that we know which fdin and fdout to set.

static void	skip_generic(t_list **tokens)
{
	t_toktype	token_type;

	token_type = get_type_from_tok((*tokens)->content);
	while (token_type == T_GENERIC && token_type != T_END)
	{
		*tokens = (*tokens)->next;
		token_type = get_type_from_tok((*tokens)->content);
	}
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

t_list	*interpreter(t_list *tokens, char **env)
{
	t_command	*cmd_data;
	t_list		*commands;

	commands = NULL;
	skip_until_generic(&tokens);
	while (get_type_from_tok(tokens->content) != T_END)
	{
		cmd_data = init_command(tokens, env);
		ft_lstadd_back(&commands, ft_lstnew(cmd_data));
		skip_generic(&tokens);
		skip_until_generic(&tokens);
	}
	return (commands);
}
