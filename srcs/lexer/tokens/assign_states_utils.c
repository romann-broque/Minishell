/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_states_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:46:12 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 17:02:14 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_state_assign(const char **word, t_qstate *state)
{
	const char	c = (*word)[0];

	if (c == END_CHAR)
		*state = E_EOF;
	else if (c == SINGLE_QUOTE)
		*state = E_QUOTE;
	else if (c == DOUBLE_QUOTE)
		*state = E_DQUOTE;
}

bool	is_assign(const char *word)
{
	static bool	(*assign_state[])(const char **, t_qstate *) = {
		start_state_assign,
		squote_state_assign,
		dquote_state_assign,
		NULL,
		word_state_assign,
	};
	t_qstate	state;
	bool		is_assign_val;

	state = ASSIGN_START;
	is_assign_val = false;
	while (state != E_EOF && is_assign_val == false)
		is_assign_val = assign_state[state](&word, &state);
	return (is_assign_val);
}
