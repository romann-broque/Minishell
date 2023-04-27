/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:17:44 by mat               #+#    #+#             */
/*   Updated: 2023/04/27 17:07:22 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	replace_special_var(t_vmachine *const machine)
{
	const char		c = machine->line[machine->index];
	char *const		last_ret_str = ft_itoa(g_global.last_ret_val);
	const size_t	index = abs_index(SPECIAL_VAR, c);
	char *const		array_str[] = {last_ret_str, ZERO_VAR};

	if (is_in_str(SEPARATORS, c) == false)
		machine->line = replace_str_free(machine->line, array_str[index],
				machine->index - 1, SPEC_VAR_LEN);
	change_state(machine->prev_state, machine);
	free(last_ret_str);
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
		--(machine->index);
		change_state(machine->prev_state, machine);
	}
}

void	translate_var(t_vmachine *const mach)
{
	char *const	var_name = get_var_name(mach);
	char *const	var_value = ft_getenv(var_name);

	free(var_name);
	if (var_value == NULL)
		mach->line = cut_string_at(mach->line,
				mach->index - (mach->word_len + 1), mach->word_len + 1);
	else
		mach->line = replace_str_free(mach->line, var_value,
				mach->index - (mach->word_len + 1), mach->word_len + 1);
	mach->index += ft_strlen_safe(var_value) - (mach->word_len + 1);
	mach->word_len = 0;
	change_state(mach->prev_state, mach);
}
