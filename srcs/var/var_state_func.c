/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_state_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:15:32 by mat               #+#    #+#             */
/*   Updated: 2023/04/02 20:22:13 by mat              ###   ########.fr       */
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
	const char	c = machine->line[machine->i];

	if (c == '\0')
		change_state(E_EOF, machine);
	else if (c == S_QUOTE)
		change_state(E_SINGLE_QUOTE, machine);
	else if (c == D_QUOTE)
		change_state(E_DOUBLE_QUOTE, machine);
	else if (c == '$')
		change_state(E_DOLLAR, machine);
	machine->i++;
}

void	d_quote_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->i];

	if (c == D_QUOTE)
		change_state(E_STD, machine);
	if (c == '$')
		change_state(E_DOLLAR, machine);
	machine->i++;
}

void	s_quote_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->i];

	if (c == S_QUOTE)
		change_state(E_STD, machine);
	machine->i++;
}

void	var_state(t_vmachine *const machine)
{
	const char	c = machine->line[machine->i];

	if (machine->word_len == 0)
		handle_var_start(machine);
	else if (is_in_var_charset(c) == true)
		machine->word_len++;
	else
	{
		translate_var(machine);
		change_state(E_STD, machine);
		machine->i = 0;
		return ;
	}
	machine->i++;
}
