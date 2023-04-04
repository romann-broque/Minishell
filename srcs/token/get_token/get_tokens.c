/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:29:42 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 10:53:14 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get_tokens :	Returns an array of tokens ready to be categorize by the lexer.
//				It uses a finite state machine strategy

t_list	*get_tokens(const char *str)
{
	static void	(*state_fct[])(t_qmachine *const) = {
		separator_state,
		single_quote_state,
		double_quote_state,
		word_state,
	};
	t_qmachine	machine;
	t_list		*tokens;

	tokens = NULL;
	if (str != NULL)
	{
		init_qmachine(&machine, str);
		while (machine.state != E_EOF)
			state_fct[machine.state](&machine);
		if (machine.tokens == NULL)
			machine.tokens = ft_lstnew(NULL);
		tokens = machine.tokens;
	}
	return (tokens);
}
