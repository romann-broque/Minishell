/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:16:21 by mat               #+#    #+#             */
/*   Updated: 2023/04/20 14:38:09 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_type_str(t_token *token)
{
	char *const	type_str_tab[] = {
		LCHEVRON, RCHEVRON, DOUBLE_LCHEVRON, DOUBLE_RCHEVRON,
		PIPE, OR, AND, NULL, NULL, NULL, END_STR
	};
	t_toktype	type;

	type = get_type_from_tok(token);
	return (ft_strdup(type_str_tab[type]));
}

void	print_pars_error(t_token *token)
{
	char *const	error_str = get_type_str(token);

	print_error("%s: %s `%s'\n", MINISHELL, PARS_ERROR, error_str);
	free(error_str);
}
