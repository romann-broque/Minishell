/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:02:35 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 10:05:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_command(t_list *tokens)
{
	char	*tmp;

	while (tokens != NULL)
	{
		tmp = get_str_from_tok(tokens->content);
		if (tmp != NULL)
		{
			((t_token *)(tokens->content))->value = expand_var(tmp);
			free(tmp);
		}
		tokens = tokens->next;
	}
}
