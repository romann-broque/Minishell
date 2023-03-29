/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:41:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/29 15:52:53 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separator_state(t_qmachine *const machine)
{
	const char	curr_char = machine->str[0];

	if (curr_char == '\0')
		machine->state = E_EOF;
	else if (is_separator(curr_char) == true)
		++(machine->str);
	else if (curr_char == '\'')
		machine->state = E_QUOTE;
	else if (curr_char == '\"')
		machine->state = E_DQUOTE;
	else
		machine->state = E_WORD;
}

static void	quote_state(t_qmachine *const machine, const char quote)
{
	const char		curr_char = machine->str[0];
	const size_t	curr_len = machine->word_len;

	if (curr_char == '\0')
	{
		add_token(machine);
		machine->state = E_EOF;
	}
	else
	{
		++(machine->word_len);
		++(machine->str);
		if (curr_len > 0 && curr_char == quote
			&& is_last_quote(machine, quote) == true)
		{
			add_token(machine);
			machine->state = E_SEPARATOR;
		}
	}
}

void	single_quote_state(t_qmachine *const machine)
{
	quote_state(machine, '\'');
}

void	double_quote_state(t_qmachine *const machine)
{
	quote_state(machine, '\"');
}

void	word_state(t_qmachine *const machine)
{
	const char	curr_char = machine->str[0];

	if (curr_char == '\0')
	{
		add_token(machine);
		machine->state = E_EOF;
	}
	else if (is_separator(curr_char) == true)
	{
		add_token(machine);
		machine->state = E_SEPARATOR;
	}
	else
	{
		++(machine->word_len);
		++(machine->str);
	}
}
