/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:41:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/29 16:58:34 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// quote_state:	generic function for single quotes and double quotes

void	separator_state(t_qmachine *const machine)
{
	update_state(machine);
	if (machine->state == E_SEPARATOR)
		++(machine->str);
	else
	{
		++(machine->word_len);
		add_token(machine);
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

void	spec_tok_state(t_qmachine *const machine)
{
	const char		*spec_tok[] = {
		OR,
		AND,
		DOUBLE_LCHEVRON,
		DOUBLE_RCHEVRON,
		LCHEVRON,
		RCHEVRON,
		PIPE,
		ASSIGN_EQ
	};

	add_spec_token(machine, spec_tok);
	machine->state = E_WORD;
}

void	word_state(t_qmachine *const machine)
{
	update_state(machine);
	if (machine->state == E_WORD)
	{
		++(machine->word_len);
		++(machine->str);
	}
	else
		add_token(machine);
}
