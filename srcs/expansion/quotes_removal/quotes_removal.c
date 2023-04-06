/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:55:56 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 18:53:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes_removal(const char *str)
{
	static void	(*state_fct[])(char **, size_t *, t_qstate *) = {
		NULL,
		squote_state_qrm,
		dquote_state_qrm,
		NULL,
		word_state_qrm
	};
	size_t		index;
	char		*new_str;
	t_qstate	state;

	new_str = ft_strdup(str);
	index = 0;
	state = E_WORD;
	while (state != E_EOF)
		state_fct[state](&new_str, &index, &state);
	return (new_str);
}
