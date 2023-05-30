/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_machine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:20:05 by mat               #+#    #+#             */
/*   Updated: 2023/05/28 12:46:38 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_state(t_vstate new_state, t_vmachine *const machine)
{
	machine->prev_state = machine->state;
	machine->state = new_state;
}

static void	init_vmachine(t_vmachine *const machine, const char *line)
{
	machine->state = E_STD;
	machine->prev_state = E_STD;
	machine->word_len = 0;
	machine->index = 0;
	machine->line = ft_strdup(line);
	if (machine->line == NULL)
		exit_alloc();
}

char	*expand_var(const char *line)
{
	static void	(*s_var_func[])(t_vmachine *const) = {
		std_state,
		d_quote_state,
		s_quote_state,
		spec_var_state,
		var_state
	};
	t_vmachine	machine;
	char		*new_line;

	new_line = NULL;
	if (line != NULL)
	{
		init_vmachine(&machine, line);
		while (machine.state != E_EOL)
			s_var_func[machine.state](&machine);
		new_line = machine.line;
	}
	return (new_line);
}
