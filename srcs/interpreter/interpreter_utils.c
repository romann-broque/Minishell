/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:44:42 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/05 09:47:13 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
