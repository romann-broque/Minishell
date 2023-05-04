/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:19 by mat               #+#    #+#             */
/*   Updated: 2023/05/03 16:06:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
