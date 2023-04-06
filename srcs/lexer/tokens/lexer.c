/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 00:45:18 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 10:14:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_lexer_format(t_list **tokens)
{
	ft_lstadd_front(tokens, ft_lstnew(init_token(T_START, NULL)));
	ft_lstadd_back(tokens, ft_lstnew(init_token(T_END, NULL)));
}

t_list	*lexer_root(const char *str)
{
	t_list	*word_lst;
	t_list	*tokens;

	word_lst = get_words(str);
	tokens = tokenizer(word_lst);
	ft_lstclear(&word_lst, free);
	return (tokens);
}

t_list	*lexer(const char *str)
{
	t_list	*tokens;

	tokens = lexer_root(str);
	put_lexer_format(&tokens);
	return (tokens);
}
