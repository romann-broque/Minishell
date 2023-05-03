/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:44:42 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 15:33:37 by rbroque          ###   ########.fr       */
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
