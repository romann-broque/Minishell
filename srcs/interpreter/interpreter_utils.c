/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:44:42 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 14:50:06 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list	*cmd_mode(t_list *tokens, t_list *env)
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
		else
		{
			if (toktype == T_GENERIC)
				process_gen(&commands, &tokens, env, assign);
			ft_lstclear(&assign, (void (*)(void *))free_var);
			assign = NULL;
		}
		tokens = tokens->next;
		toktype = get_type_from_tok(tokens->content);
	}
	ft_lstclear(&assign, (void (*)(void *))free_var);
	return (commands);
}

bool	is_assign_mode(t_list *tokens)
{
	t_toktype	type;

	type = get_type_from_tok(tokens->content);
	while (type != T_END)
	{
		if (type != T_ASSIGN && type != T_START)
			return (false);
		tokens = tokens->next;
		type = get_type_from_tok(tokens->content);
	}
	return (true);
}
