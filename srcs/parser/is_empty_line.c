/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:13:42 by mat               #+#    #+#             */
/*   Updated: 2023/04/11 10:26:53 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_empty_line(t_list *tokens)
{
	return (ft_lstsize(tokens) == 3
		&& get_type_from_tok(tokens->content) == T_START
		&& tokens->next->content == NULL
		&& get_type_from_tok(tokens->next->next->content) == T_END);
}
