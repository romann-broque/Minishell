/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:26:48 by mat               #+#    #+#             */
/*   Updated: 2023/04/04 16:58:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command(t_list *token_lst)
{
	size_t	i;

	i = 0;
	while (token_lst != NULL)
	{
		if (token_lst->content != NULL)
			printf("Element %zu : [%s]\n", i + 1,
				(char*)(token_lst->content));
		token_lst = token_lst->next;
		++i;
	}
}
