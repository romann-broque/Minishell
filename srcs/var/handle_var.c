/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:17:44 by mat               #+#    #+#             */
/*   Updated: 2023/04/02 20:27:58 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_var_start(t_vmachine *const machine)
{
	const char	c = machine->line[machine->i];

	if (is_in_var_charset(c) == true)
		machine->word_len++;
	else
	{
		change_state(E_STD, machine);
		if (is_special_var(c) == true)
		{
			if (c == '?')
				replace_str(machine->line, "LAST_REV_VAL",
					machine->i - 1, SPEC_VAR_LEN);
			if (c == '0')
				replace_str(machine->line, "minishell",
					machine->i - 1, SPEC_VAR_LEN);
		}
		else
			replace_str(machine->line, "", machine->i - 1, SPEC_VAR_LEN);
	}
}

static char	*get_var_name(t_vmachine *const machine)
{
	char	*var_start;
	char	*var_name;

	var_start = machine->line + machine->i - machine->word_len;
	var_name = ft_strndup(var_start, machine->word_len);
	return (var_name);
}

void	translate_var(t_vmachine *const machine)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(machine);
	var_value = getenv(var_name);
	free(var_name);
	if (var_value == NULL)
		replace_str(machine->line, "", machine->i - 1, machine->word_len + 1);
	else
		replace_str(machine->line, var_value,
			machine->i - 1, machine->word_len + 1);
}
