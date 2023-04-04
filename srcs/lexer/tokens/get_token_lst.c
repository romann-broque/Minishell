/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 00:45:18 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 00:55:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_token_lst(const char *str)
{
	char *const	line_w_var = expand_var(str);
	t_list		*word_lst;
	t_list		*tokens;

	word_lst = get_words(line_w_var);
	tokens = tokenizer(word_lst);
	free(line_w_var);
	ft_lstclear(&word_lst, free);
	return (tokens);
}
