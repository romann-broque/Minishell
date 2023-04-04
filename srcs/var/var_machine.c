/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_machine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:20:05 by mat               #+#    #+#             */
/*   Updated: 2023/04/04 14:21:00 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_state(t_vstate new_state, t_vmachine *const machine)
{
	machine->prev_state = machine->state;
	machine->state = new_state;
}

static void	init_vmachine(t_vmachine *const machine, char *line)
{
	machine->state = E_STD;
	machine->word_len = 0;
	machine->index = 0;
	machine->line = ft_strdup(line);
}

void	reboot_vmachine(t_vmachine *const machine)
{
	change_state(E_STD, machine);
	machine->index = 0;
	machine->word_len = 0;
}

char	*expand_var(char *line)
{
	static void	(*s_var_func[])(t_vmachine *const) = {
		std_state,
		d_quote_state,
		s_quote_state,
		var_state
	};
	t_vmachine	machine;
	char		*new_line;

	new_line = line;
	if (new_line != NULL)
	{
		init_vmachine(&machine, line);
		while (machine.state != E_EOL)
			s_var_func[machine.state](&machine);
		new_line = machine.line;
	}
	return (new_line);
}
