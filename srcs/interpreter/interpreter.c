/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:19 by mat               #+#    #+#             */
/*   Updated: 2023/05/23 11:50:30 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_assign_mode(t_list *tokens)
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

static void	exec_assign_tok(t_token *tok)
{
	t_var	*var;

	if (tok->type == T_ASSIGN)
	{
		var = init_var_from_str(tok->value);
		if (var != NULL)
			update_var(var->key, var->value, SET_MASK);
		free_var(var);
	}
}

t_list	*interpreter(t_list *tokens, t_list *env)
{
	if (is_assign_mode(tokens) == true)
		ft_lstiter(tokens, (void (*)(void *))exec_assign_tok);
	else
		return (cmd_mode(tokens, env));
	return (NULL);
}
