/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:17:44 by mat               #+#    #+#             */
/*   Updated: 2023/04/03 17:18:16 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_special_var(t_vmachine *const machine)
{
	const char		c = machine->line[machine->i];
	static char		array_str[][STR_LEN_MAX + 1] = {
		"LAST_REV_VAL",
		"minishell"
	};
	const size_t	index = abs_index(SPECIAL_VAR, c);

	machine->line = replace_and_free(machine->line, array_str[index],
			machine->i - 1, SPEC_VAR_LEN);
}

void	handle_var_start(t_vmachine *const machine)
{
	const char	c = machine->line[machine->i];

	if (is_in_var_start_charset(c) == true)
	{
		machine->i++;
		machine->word_len++;
	}
	else if (c != '\0' && is_in_str(SEPARATORS, c) == false)
	{
		if (is_special_var(c) == true)
			replace_special_var(machine);
		else
			machine->line = replace_and_free(machine->line, "",
					machine->i - 1, SPEC_VAR_LEN);
		reboot_vmachine(machine);
	}
	else
		change_state(E_STD, machine);
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
		machine->line = replace_and_free(machine->line, "",
				machine->i - 1 - machine->word_len, machine->word_len + 1);
	else
		machine->line = replace_and_free(machine->line, var_value,
				machine->i - 1 - machine->word_len, machine->word_len + 1);
	reboot_vmachine(machine);
}
