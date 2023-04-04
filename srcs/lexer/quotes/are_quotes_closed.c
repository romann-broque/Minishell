/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_quotes_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:03 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/30 15:37:38 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	out_of_quote(const char **str, t_qstate *state)
{
	if (**str == END_CHAR)
		*state = E_EOF;
	else if (**str == SINGLE_QUOTE)
		*state = E_QUOTE;
	else if (**str == DOUBLE_QUOTE)
		*state = E_DQUOTE;
	++(*str);
	return (true);
}

static bool	in_quote(const char **str, t_qstate *state, const char quote)
{
	if (**str == END_CHAR)
		return (false);
	else if (**str == quote)
		*state = E_SEPARATOR;
	++(*str);
	return (true);
}

static bool	in_single_quote(const char **str, t_qstate *state)
{
	return (in_quote(str, state, SINGLE_QUOTE));
}

static bool	in_double_quote(const char **str, t_qstate *state)
{
	return (in_quote(str, state, DOUBLE_QUOTE));
}

bool	are_quotes_closed(const char *str)
{
	static bool	(*is_closed[])(const char **, t_qstate *) = {
		out_of_quote,
		in_single_quote,
		in_double_quote,
	};
	t_qstate	state;

	state = E_SEPARATOR;
	if (str != NULL)
	{
		while (state != E_EOF && is_closed[state](&str, &state) == true)
			;
	}
	return (str == NULL || state == E_EOF);
}
