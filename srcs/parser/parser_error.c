/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:16:21 by mat               #+#    #+#             */
/*   Updated: 2023/04/27 22:33:51 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_type_str(t_token *token)
{
	char *const	type_str_tab[] = {
		LCHEVRON, RCHEVRON, DOUBLE_LCHEVRON, DOUBLE_RCHEVRON,
		PIPE, OR, AND, SEP, NULL, NULL, NULL, NULL, END_STR
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
