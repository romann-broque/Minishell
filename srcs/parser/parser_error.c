/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:16:21 by mat               #+#    #+#             */
/*   Updated: 2023/04/14 17:42:22 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_type_str(t_token *token)
{
	char *const	type_str_tab[] = {
		"<", ">", "<<", ">>", "|", "||", "&&",
		"WORD=WORD", "WORD", "START", "END"
	};
	t_toktype	type;

	type = get_type_from_tok(token);
	return (ft_strdup(type_str_tab[type]));
}

void	print_pars_error(t_token *token)
{
	char	*error_str;

	error_str = get_type_str(token);
	ft_dprintf(STDERR_FILENO, PARS_ERROR"`%s'\n", error_str);
	free(error_str);
}
