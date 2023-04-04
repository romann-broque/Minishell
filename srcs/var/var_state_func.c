/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_state_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:15:32 by mat               #+#    #+#             */
/*   Updated: 2023/04/03 18:19:58 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_state(t_vstate new_state, t_vmachine *const machine)
{
	machine->prev_state = machine->state;
	machine->state = new_state;
}

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
		change_state(E_DOLLAR, machine);
	machine->index++;
}

void	d_quote_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (c == DOUBLE_QUOTE)
		change_state(E_STD, machine);
	else if (c == DOLLAR_SIGN)
		change_state(E_DOLLAR, machine);
	machine->index++;
}

void	s_quote_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (c == SINGLE_QUOTE)
		change_state(E_STD, machine);
	machine->index++;
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
