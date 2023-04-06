/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qrm_states.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:49:25 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 18:50:29 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_state_qrm(const char c, t_qstate *state)
{
	update_state_assign(c, state);
}

void	word_state_qrm(char **word, size_t *index, t_qstate *state)
{
	const char	c = (*word)[*index];

	update_state_qrm(c, state);
	if (*state == E_WORD)
		++(*index);
}

static void	quote_state_qrm(
	char **word,
	size_t *index,
	t_qstate *state,
	const char quote)
{
	const char	prev_char = (*word)[*index];
	static bool	is_opening_quote = true;

	++(*index);
	if (is_opening_quote == false && prev_char == quote)
	{
		*word = replace_and_free(*word, EMPTY_STR, *index - 1, 1);
		--(*index);
		*state = E_WORD;
		is_opening_quote = true;
	}
	else
	{
		if (is_opening_quote == true)
		{
			*word = replace_and_free(*word, EMPTY_STR, *index - 1, 1);
			--(*index);
		}
		is_opening_quote = false;
	}
}

void	squote_state_qrm(char **word, size_t *index, t_qstate *state)
{
	quote_state_qrm(word, index, state, SINGLE_QUOTE);
}

void	dquote_state_qrm(char **word, size_t *index, t_qstate *state)
{
	quote_state_qrm(word, index, state, DOUBLE_QUOTE);
}
