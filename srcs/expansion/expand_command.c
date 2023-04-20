/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:02:35 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/20 14:15:35 by mat              ###   ########.fr       */
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

static int	is_empty_tok(t_token *token, char *data_ref)
{
	if (token->type == T_START || token->type == T_END)
		return (IGNORE_TOK);
	return (ft_strcmp(token->value, data_ref));
}

static void	rm_empty_tok(t_list **tokens)
{
	ft_list_remove_if(tokens, EMPTY_STR,
		is_empty_tok, (void (*)(void *))free_token);
}

void	expand_command(t_list **tokens)
{
	ft_lstiter(*tokens, (void (*)(void *))expand);
	rm_empty_tok(tokens);
}
