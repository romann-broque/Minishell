/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:41:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/28 22:25:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_separator(const char c)
{
	return (ft_strchr(SEPARATORS, c));
}

void	separator_state(t_qmachine *const machine)
{
	const char	curr_char = machine->str[0];

	if (curr_char == '\0')
		machine->state = E_EOF;
	else if (is_separator(curr_char) == true)
		++(machine->str);
	else
	{
		if (curr_char == '\'')
			machine->state = E_QUOTE;
		else if (curr_char == '\"')
			machine->state = E_DQUOTE;
		else
			machine->state = E_WORD;
	}
}

void	single_quote_state(t_qmachine *const machine)
{
	const char		curr_char = machine->str[0];
	const size_t	curr_index = machine->index;

	if (curr_char == '\0')
	{
		add_token(machine);
		machine->state = E_EOF;
	}
	else
	{
		++(machine->index);
		++(machine->str);
		if (curr_index > 0 && curr_char == '\'')
		{
			if (is_separator(machine->str[0]) == true)
				add_token(machine);
			machine->state = E_SEPARATOR;
		}
	}
}

void	double_quote_state(t_qmachine *const machine)
{
	const char		curr_char = machine->str[0];
	const size_t	curr_index = machine->index;

	if (curr_char == '\0')
	{
		add_token(machine);
		machine->state = E_EOF;
	}
	else
	{
		++(machine->index);
		++(machine->str);
		if (curr_index > 0 && curr_char == '\"')
		{
			if (is_separator(machine->str[0]) == true)
				add_token(machine);
			machine->state = E_SEPARATOR;
		}
	}
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
		++(machine->index);
	++(machine->str);
}
