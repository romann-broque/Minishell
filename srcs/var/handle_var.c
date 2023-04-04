/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:17:44 by mat               #+#    #+#             */
/*   Updated: 2023/04/04 17:48:01 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_special_var(t_vmachine *const machine)
{
	const char		c = machine->line[machine->index];
	static char		array_str[][STR_LEN_MAX + 1] = {
		QMARK_VAR,
		ZERO_VAR
	};
	const size_t	index = abs_index(SPECIAL_VAR, c);

	if (is_in_str(SEPARATORS, c) == false)
		machine->line = replace_and_free(machine->line, array_str[index],
				machine->index - 1, SPEC_VAR_LEN);
	change_state(machine->prev_state, machine);
}

static char	*get_var_name(t_vmachine *const machine)
{
	const char	*var_start = machine->line + machine->index - machine->word_len;

	return (ft_strndup(var_start, machine->word_len));
}

void	handle_var_start(t_vmachine *const machine)
{
	const char	c = machine->line[machine->index];

	if (is_in_var_start_charset(c) == true)
	{
		machine->index++;
		machine->word_len++;
	}
	else
	{
		machine->line = cut_string_at(machine->line,
				machine->index - 1, WRONG_VAR_LEN);
		change_state(machine->prev_state, machine);
	}
}

void	translate_var(t_vmachine *const machine)
{
	char *const	var_name = get_var_name(machine);
	char *const	var_value = getenv(var_name);

	free(var_name);
	if (var_value == NULL)
		machine->line = cut_string_at(machine->line,
				machine->index - 1 - machine->word_len, machine->word_len + 1);
	else
		machine->line = replace_and_free(machine->line, var_value,
				machine->index - 1 - machine->word_len, machine->word_len + 1);
	machine->index += ft_strlen_safe(var_value) - machine->word_len - 1;
	machine->word_len = 0;
	change_state(machine->prev_state, machine);
}
