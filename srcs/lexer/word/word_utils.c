/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:51:57 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 15:49:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_separator(const char c)
{
	return (ft_strchr(SEPARATORS, c));
}

void	update_state(t_qmachine *const machine)
{
	const char	c = machine->str[0];

	if (c == END_CHAR)
		machine->state = E_EOF;
	else if (is_in_str(TOK_LEXEME, c) == true)
		machine->state = E_SPEC_TOK;
	else if (is_separator(c) == true)
		machine->state = E_SEPARATOR;
	else if (c == SINGLE_QUOTE)
		machine->state = E_QUOTE;
	else if (c == DOUBLE_QUOTE)
		machine->state = E_DQUOTE;
	else
		machine->state = E_WORD;
}

void	init_qmachine(t_qmachine *const machine, const char *str)
{
	machine->state = E_SEPARATOR;
	machine->word_len = 0;
	machine->str = str;
	machine->words = NULL;
}

void	quote_state(t_qmachine *const machine, const char quote)
{
	const char	prev_char = machine->str[0];
	static bool	is_opening_quote = true;

	++(machine->word_len);
	++(machine->str);
	if (is_opening_quote == false && prev_char == quote)
	{
		update_state(machine);
		if (machine->state == E_EOF || machine->state == E_SEPARATOR)
			add_token(machine);
		is_opening_quote = true;
	}
	else
		is_opening_quote = false;
}
