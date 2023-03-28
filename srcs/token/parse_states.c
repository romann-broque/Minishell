/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:41:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/28 18:47:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_separator(const char c)
{
	return (ft_strchr(SEPARATORS, c));
}

void	separator_state(t_qmachine *machine)
{
	const char	curr_char = machine->str[machine->abs_index];

	if (curr_char == '\0')
		machine->state = E_EOF;
	else if (is_separator(curr_char) == false)
	{
		machine->index = 0;
		machine->state = E_WORD;
	}
	else
		++(machine->abs_index);
}

void	simple_quote_state(t_qmachine *machine)
{
	const char	curr_char = machine->str[machine->abs_index];

	if (curr_char == '\0')
		machine->state = E_EOF;
	else if (curr_char == '\'')
	{
		add_token(machine);
		machine->state = E_SEPARATOR;
	}
	++(machine->abs_index);
	++(machine->index);
}

void	double_quote_state(t_qmachine *machine)
{
	const char	curr_char = machine->str[machine->abs_index];

	if (curr_char == '\0')
		machine->state = E_EOF;
	else if (curr_char == '\"')
		machine->state = E_SEPARATOR;
	++(machine->abs_index);
	++(machine->index);
}

void	word_state(t_qmachine *machine)
{
	const char	curr_char = machine->str[machine->abs_index];

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
		++(machine->index);
	++(machine->abs_index);
}
