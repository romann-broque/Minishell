/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:29:42 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/28 22:26:00 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_qmachine(t_qmachine *machine, const char *str)
{
	machine->state = E_SEPARATOR;
	machine->index = 0;
	machine->str = str;
	machine->tokens = NULL;
}

static void	print_list(t_list *lst)
{
	while (lst != NULL)
	{
		printf("[%s]\n", (char *)(lst->content));
		lst = lst->next;
	}
}

char	**get_tokens(const char *str)
{
	static void	(*state_fct[])(t_qmachine *const) = {
		separator_state,
		single_quote_state,
		double_quote_state,
		word_state,
	};
	t_qmachine	machine;
	char		**tokens;

	tokens = NULL;
	if (str != NULL)
	{
		init_qmachine(&machine, str);
		while (machine.state != E_EOF)
			state_fct[machine.state](&machine);
		print_list(machine.tokens);
		tokens = dup_strs_from_lst(machine.tokens);
		ft_lstclear(&(machine.tokens), free);
	}
	return (tokens);
}
