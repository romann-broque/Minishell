/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:19 by mat               #+#    #+#             */
/*   Updated: 2023/05/03 11:33:32 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*init_command(
	t_list *tokens,
	t_list *env,
	t_list *local_env
	)
{
	t_command	*cmd_data;

	cmd_data = (t_command *)malloc(sizeof(t_command));
	if (cmd_data != NULL)
	{
		cmd_data->command = get_arg_array(tokens);
		if (cmd_data->command == NULL)
			return (NULL);
		cmd_data->env = dup_envs_lst_to_array(env, local_env);
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

	token_type = get_type_from_tok((*tokens)->next->content);
	while ((token_type == T_GENERIC || token_type == T_ASSIGN)
		&& token_type != T_END)
	{
		*tokens = (*tokens)->next;
		token_type = get_type_from_tok((*tokens)->next->content);
	}
}

static void	process_gen(
	t_list **commands,
	t_list **tokens,
	t_list *env,
	t_list *local_env
	)
{
	t_command	*cmd_data;

	cmd_data = init_command(*tokens, env, local_env);
	ft_lstadd_back(commands, ft_lstnew(cmd_data));
	skip_generic(tokens);
}

static void	process_assign(t_list **assign, t_list *tokens)
{
	t_token *const	tok = tokens->content;
	t_var *const	var = init_var_from_str(tok->value);

	ft_lstadd_back(assign, ft_lstnew(var));
}

// static void	print_var_list(t_list *assign)
// {
// 	t_var	*var;

// 	while (assign != NULL)
// 	{
// 		var = assign->content;
// 		printf("%s=%s\n", var->key, var->value);
// 		assign = assign->next;
// 	}
// }

t_list	*interpreter(t_list *tokens, t_list *env)
{
	t_list		*assign;
	t_list		*commands;
	t_toktype	toktype;

	commands = NULL;
	assign = NULL;
	toktype = get_type_from_tok(tokens->content);
	while (toktype != T_END)
	{
		if (toktype == T_ASSIGN)
			process_assign(&assign, tokens);
		else if (toktype == T_GENERIC)
			process_gen(&commands, &tokens, env, assign);
		else
		{
			ft_lstclear(&assign, (void (*)(void *))free_var);
			assign = NULL;
		}
		tokens = tokens->next;
		toktype = get_type_from_tok(tokens->content);
	}
	return (commands);
}
	// print_var_list(assign);
