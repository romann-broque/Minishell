/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_to_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:21:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/29 17:10:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_str_in_list(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	ft_lstadd_back(lst, new);
}

static void	add_part_in_list(t_list **lst, const char *str, const size_t len)
{
	add_str_in_list(lst, ft_strndup(str, len));
}

void	add_token(t_qmachine *machine)
{
	add_part_in_list(&(machine->tokens),
		machine->str - machine->word_len,
		machine->word_len);
	machine->word_len = 0;
}
