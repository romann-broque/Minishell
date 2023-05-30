/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:09:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 17:49:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	*g_global;

t_list	*get_cmd_env(t_list *glob_env, t_list *loc_env)
{
	t_var	*var;
	t_list	*new;

	new = NULL;
	while (glob_env != NULL)
	{
		var = glob_env->content;
		if (var->flags & EXPORT_MASK && var->flags & SET_MASK)
			ft_lstaddback_fatal(&new, dup_var(var), (void (*)(void *))free_var);
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

void	process_assign(t_list **assign, t_list *tokens)
{
	t_token *const	tok = tokens->content;
	t_var *const	tmp_var = init_var_from_str(tok->value);

	ft_lstaddback_fatal(assign, tmp_var, (void (*)(void *))free_var);
}

void	clear_local_env(t_list **env)
{
	ft_lstclear(env, (void (*)(void *))free_var);
	*env = NULL;
}

static size_t	get_nb_cmd(t_list *tokens)
{
	t_toktype	type;
	size_t		nb;

	nb = 0;
	while (tokens != NULL)
	{
		type = get_type_from_tok(tokens->content);
		nb += (type == T_START || type == T_PIPE);
		tokens = tokens->next;
	}
	return (nb);
}

void	init_cmd_mode(t_list *tokens)
{
	g_global->prev_pipe = INVALID_FD;
	g_global->cmd_index = 0;
	g_global->cmd_nbr = get_nb_cmd(tokens);
}
