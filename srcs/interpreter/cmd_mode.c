/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:32:46 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 17:51:34 by rbroque          ###   ########.fr       */
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

static t_list	*get_cmd_env(t_list *glob_env, t_list *loc_env)
{
	t_var	*var;
	t_list	*new;

	new = NULL;
	while (glob_env != NULL)
	{
		var = glob_env->content;
		if (var->flags & EXPORT_MASK)
			ft_lstadd_back(&new, ft_lstnew(dup_var(var)));
		glob_env = glob_env->next;
	}
	while (loc_env != NULL)
	{
		var = loc_env->content;
		change_var(var->key, var->value, var->flags, &new);
		loc_env = loc_env->next;
	}
	return (new);
}

static void	process_gen(
	t_list **commands,
	t_list **tokens,
	t_list *env,
	t_list *local_env
	)
{
	t_command	*cmd_data;
	t_list		*cmd_env;

	cmd_env = get_cmd_env(env, local_env);
	cmd_data = init_command(*tokens, cmd_env);
	ft_lstadd_back(commands, ft_lstnew(cmd_data));
	ft_lstclear(&cmd_env, (void (*)(void *))free_var);
	skip_generic(tokens);
}

static void	process_assign(t_list **assign, t_list *tokens)
{
	t_token *const	tok = tokens->content;
	t_var *const	tmp_var = init_var_from_str(tok->value);

	ft_lstadd_back(assign, ft_lstnew(tmp_var));
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
