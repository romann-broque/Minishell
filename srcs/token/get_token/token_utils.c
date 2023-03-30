/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:51:57 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/30 10:41:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_separator(const char c)
{
	return (ft_strchr(SEPARATORS, c));
}

void	change_state(t_qmachine *const machine)
{
	const char	c = machine->str[0];

	if (c == END_CHAR)
		machine->state = E_EOF;
	else if (is_separator(c) == true)
		machine->state = E_SEPARATOR;
	else if (c == SINGLE_QUOTE)
		machine->state = E_QUOTE;
	else if (c == DOUBLE_QUOTE)
		machine->state = E_DQUOTE;
	else
		machine->state = E_WORD;
}
