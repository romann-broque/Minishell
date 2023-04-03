/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_machine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:20:05 by mat               #+#    #+#             */
/*   Updated: 2023/04/02 20:07:38 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vmachine(t_vmachine *const machine, char *line)
{
	machine->state = E_STD;
	machine->word_len = 0;
	machine->i = 0;
	machine->line = line;
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
		while (machine.state != E_EOF)
			s_var_func[machine.state](&machine);
	}
	return (new_line);
}
