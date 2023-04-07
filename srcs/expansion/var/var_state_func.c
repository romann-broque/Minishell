/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_state_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:15:32 by mat               #+#    #+#             */
/*   Updated: 2023/04/07 12:02:53 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (c == END_CHAR)
		change_state(E_EOL, machine);
	else if (c == SINGLE_QUOTE)
		change_state(E_SINGLE_QUOTE, machine);
	else if (c == DOUBLE_QUOTE)
		change_state(E_DOUBLE_QUOTE, machine);
	else if (c == DOLLAR_SIGN)
		change_state(E_SPEC_VAR, machine);
	machine->index++;
}

void	d_quote_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (c == DOUBLE_QUOTE)
		change_state(E_STD, machine);
	else if (c == DOLLAR_SIGN)
		change_state(E_SPEC_VAR, machine);
	machine->index++;
}

void	s_quote_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (c == SINGLE_QUOTE)
		change_state(E_STD, machine);
	machine->index++;
}

void	spec_var_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (is_separator(c))
		machine->state = machine->prev_state;
	else if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
	{
		machine->line = cut_string_at(machine->line, machine->index - 1, 1);
		--(machine->index);
		machine->state = machine->prev_state;
	}
	else if (is_special_var(c))
	{
		replace_special_var(machine);
		machine->index++;
	}
	else
		machine->state = E_VAR;
}

void	var_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (machine->word_len == 0)
		handle_var_start(machine);
	else if (is_in_var_charset(c) == true)
	{
		machine->index++;
		machine->word_len++;
	}
	else
		translate_var(machine);
}
