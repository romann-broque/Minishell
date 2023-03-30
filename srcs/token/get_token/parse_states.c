/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:41:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/30 10:45:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separator_state(t_qmachine *const machine)
{
	change_state(machine);
	if (machine->state == E_SEPARATOR)
		++(machine->str);
}

static void	quote_state(t_qmachine *const machine, const char quote)
{
	const char	curr_char = machine->str[0];
	static bool	is_first_quote = true;

	if (curr_char == '\0')
	{
		add_token(machine);
		machine->state = E_EOF;
		is_first_quote = true;
	}
	else
	{
		++(machine->word_len);
		++(machine->str);
		if (is_first_quote == false && curr_char == quote)
		{
			change_state(machine);
			if (machine->state == E_EOF || machine->state == E_SEPARATOR)
				add_token(machine);
			is_first_quote = true;
		}
		else
			is_first_quote = false;
	}
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
	change_state(machine);
	if (machine->state == E_EOF || machine->state == E_SEPARATOR)
		add_token(machine);
	else if (machine->state == E_WORD)
	{
		++(machine->word_len);
		++(machine->str);
	}
}
