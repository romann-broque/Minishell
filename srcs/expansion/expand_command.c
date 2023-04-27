/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:02:35 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/27 18:36:42 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(t_token *token)
{
	char	*tmp;

	if (token != NULL)
	{
		tmp = token->value;
		if (tmp != NULL)
			token->value = expand_var(tmp);
		free(tmp);
	}
}

void	expand_command(t_list **tokens)
{
	flag_var(*tokens);
	ft_lstiter(*tokens, (void (*)(void *))expand);
	rm_empty_var(tokens);
}
