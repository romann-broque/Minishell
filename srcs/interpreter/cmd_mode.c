/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:32:46 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/23 14:52:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	generate_cmd(
	t_list **cmd_lst,
	t_list **tokens,
	t_list *env,
	t_list *local_env
	)
{
	t_command *const	new_cmd = ft_lstlast(*cmd_lst)->content;
	t_list				*cmd_env;
	t_toktype			toktype;

	cmd_env = get_cmd_env(env, local_env);
	new_cmd->env = dup_env_lst_to_array(cmd_env);
	new_cmd->command = get_arg_array(*tokens);
	toktype = get_type_from_tok((*tokens)->content);
	while (toktype != T_END && toktype != T_PIPE)
	{
		if (toktype == T_GENERIC || toktype == T_ASSIGN)
			append_to_arg_array(new_cmd, *tokens);
		else
		{
			update_fds(toktype, (*tokens)->next->content, new_cmd);
			*tokens = (*tokens)->next;
		}
		toktype = get_type_from_tok((*tokens)->next->content);
		if (toktype != T_PIPE)
		{
			*tokens = (*tokens)->next;
			toktype = get_type_from_tok((*tokens)->content);
		}
	}
	ft_lstclear(&cmd_env, (void (*)(void *))free_var);
}

static void	add_cmd(t_list **cmd_lst)
{
	t_command	*cmd;

	g_global.cmd_nbr++;
	cmd = init_command();
	ft_lstadd_back(cmd_lst, ft_lstnew(cmd));
	add_deallocator(ft_lstlast(*cmd_lst), free);
	add_deallocator(cmd, (void (*)(void *))free_command);
}

static void	process_tok(
	t_list **cmd_lst,
	t_list **tokens,
	t_list *env,
	t_list **local_env
	)
{
	t_toktype	toktype;

	toktype = get_type_from_tok((*tokens)->content);
	if (toktype == T_START || toktype == T_PIPE)
		add_cmd(cmd_lst);
	else if (toktype == T_ASSIGN)
		process_assign(local_env, *tokens);
	else if (toktype == T_GENERIC)
	{
		generate_cmd(cmd_lst, tokens, env, *local_env);
		clear_local_env(local_env);
	}
	else
	{
		update_fds(toktype, (*tokens)->next->content,
			ft_lstlast(*cmd_lst)->content);
		*tokens = (*tokens)->next;
	}
}

t_list	*cmd_mode(t_list *tokens, t_list *env)
{
	t_list		*commands;
	t_list		*local_env;
	t_toktype	toktype;

	commands = NULL;
	local_env = NULL;
	toktype = get_type_from_tok(tokens->content);
	while (toktype != T_END)
	{
		process_tok(&commands, &tokens, env, &local_env);
		toktype = get_type_from_tok(tokens->content);
		if (toktype != T_END)
			tokens = tokens->next;
		toktype = get_type_from_tok(tokens->content);
	}
	clear_local_env(&local_env);
	return (commands);
}
