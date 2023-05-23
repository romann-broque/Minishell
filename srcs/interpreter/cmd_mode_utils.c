/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:09:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/23 11:51:44 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_cmd_env(t_list *glob_env, t_list *loc_env)
{
	t_var	*var;
	t_list	*new;

	new = NULL;
	while (glob_env != NULL)
	{
		var = glob_env->content;
		if (var->flags & EXPORT_MASK && var->flags & SET_MASK)
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

void	process_assign(t_list **assign, t_list *tokens)
{
	t_token *const	tok = tokens->content;
	t_var *const	tmp_var = init_var_from_str(tok->value);

	ft_lstadd_back(assign, ft_lstnew(tmp_var));
}

void	clear_local_env(t_list **env)
{
	ft_lstclear(env, (void (*)(void *))free_var);
	*env = NULL;
}
