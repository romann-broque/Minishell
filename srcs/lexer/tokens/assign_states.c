/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:03:27 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 18:08:24 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	start_state_assign(const char **word, t_qstate *state)
{
	if (index_of(*word, EQUAL_SIGN) > 0)
		*state = E_WORD;
	else
		*state = E_EOF;
	return (false);
}

bool	word_state_assign(const char **word, t_qstate *state)
{
	const char	c = (*word)[0];

	if (c == EQUAL_SIGN)
		return (true);
	update_state_assign(c, state);
	if (*state == E_WORD)
		++(*word);
	return (false);
}

static bool	quote_state_assign(
	const char **word,
	t_qstate *state,
	const char quote)
{
	const char	prev_char = (*word)[0];
	static bool	is_opening_quote = true;

	++(*word);
	if (is_opening_quote == false && prev_char == quote)
	{
		*state = E_WORD;
		is_opening_quote = true;
	}
	else
		is_opening_quote = false;
	return (false);
}

bool	squote_state_assign(const char **word, t_qstate *state)
{
	return (quote_state_assign(word, state, SINGLE_QUOTE));
}

bool	dquote_state_assign(const char **word, t_qstate *state)
{
	return (quote_state_assign(word, state, DOUBLE_QUOTE));
}
