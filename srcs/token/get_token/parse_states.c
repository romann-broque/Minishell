/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:41:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/31 12:05:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// quote_state:	generic function for single quotes and double quotes

static void	quote_state(t_qmachine *const machine, const char quote)
{
	const char	prev_char = machine->str[0];
	static bool	is_opening_quote = true;

	++(machine->word_len);
	++(machine->str);
	if (is_opening_quote == false && prev_char == quote)
	{
		update_state(machine);
		if (machine->state == E_EOF || machine->state == E_SEPARATOR)
			add_token(machine);
		is_opening_quote = true;
	}
	else
		is_opening_quote = false;
}

void	separator_state(t_qmachine *const machine)
{
	update_state(machine);
	if (machine->state == E_SEPARATOR)
		++(machine->str);
}

void	single_quote_state(t_qmachine *const machine)
{
	quote_state(machine, SINGLE_QUOTE);
}

void	double_quote_state(t_qmachine *const machine)
{
	quote_state(machine, DOUBLE_QUOTE);
}

void	word_state(t_qmachine *const machine)
{
	update_state(machine);
	if (machine->state == E_EOF || machine->state == E_SEPARATOR)
		add_token(machine);
	else if (machine->state == E_WORD)
	{
		++(machine->word_len);
		++(machine->str);
	}
}
