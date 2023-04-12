/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:29:42 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 15:48:37 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get_words :	Returns a list of words ready to be categorize by the lexer.
//				It uses a finite state machine strategy

t_list	*get_words(const char *str)
{
	static void	(*state_fct[])(t_qmachine *const) = {
		separator_state,
		single_quote_state,
		double_quote_state,
		spec_tok_state,
		word_state,
	};
	t_qmachine	machine;
	t_list		*words;

	words = NULL;
	if (str != NULL)
	{
		init_qmachine(&machine, str);
		while (machine.state != E_EOF)
			state_fct[machine.state](&machine);
		if (machine.words == NULL)
			machine.words = ft_lstnew(NULL);
		words = machine.words;
	}
	return (words);
}
