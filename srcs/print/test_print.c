/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:08:04 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 11:09:23 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token, const size_t index)
{
	if (token->value != NULL)
		printf("Element %lu : type=[%u]; value=[%s]\n",
			index, token->type, token->value);
}

void	print_command(t_list *token_lst)
{
	size_t	i;

	i = 0;
	while (token_lst != NULL)
	{
		if (token_lst->content != NULL)
			printf("Element %zu : [%s]\n", i + 1,
				((t_token *)(token_lst->content))->value);
		token_lst = token_lst->next;
		++i;
	}
}
