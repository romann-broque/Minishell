/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:35:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 11:49:35 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

#define MAX_TOKEN_LEN 20

static void	compare_tok_lst(const char *str, const char exp_tok[][MAX_TOKEN_LEN + 1], const size_t size)
{
	t_list	*tok_lst;
	char	**ret_tok;
	size_t	i;

	tok_lst = get_tokens(str);
	ret_tok = dup_strs_from_lst(tok_lst);
	i = 0;
	while (i < size)
	{
		CU_ASSERT_STRING_EQUAL(ret_tok[i], exp_tok[i]);
		++i;
	}
	ft_lstclear(&tok_lst, free);
	free_strs(ret_tok);
}

void	get_token__test(void)
{
	const char		*str1 = "hello my friend";
	const char		exp_tok1[][MAX_TOKEN_LEN + 1] = {
		"hello",
		"my",
		"friend"
	};

	compare_tok_lst(str1, exp_tok1, 3);
}
