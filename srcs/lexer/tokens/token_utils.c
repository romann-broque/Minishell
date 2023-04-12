/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 00:59:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/11 15:48:01 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(t_toktype type, char *value)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (tok != NULL)
	{
		tok->type = type;
		tok->value = NULL;
		if (value != NULL)
			tok->value = ft_strdup(value);
	}
	return (tok);
}

t_toktype	get_type_from_tok(t_token *tok)
{
	return (tok->type);
}

char	*get_str_from_tok(t_token *tok)
{
	if (tok != NULL)
		return (tok->value);
	return (NULL);
}

void	free_token(t_token *tok)
{
	if (tok != NULL)
		free(tok->value);
	free(tok);
}
