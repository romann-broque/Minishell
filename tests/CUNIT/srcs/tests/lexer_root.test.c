/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_root.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:12:25 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 16:43:36 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

static bool	are_same_token(const t_token *tok1, const t_token *tok2)
{
	return ((tok1 == tok2)
		|| (tok1->type == tok2->type && streq(tok1->value, tok2->value)));
}

static void	compare_tok_lst(const char *str, const t_token exp_tok[], const size_t size)
{
	size_t	fail_count;
	t_list	*tok_lst;
	t_list	*tmp_lst;
	size_t	i;

	fail_count = 0;
	tok_lst = lexer_root(str);
	tmp_lst = tok_lst;
	i = 0;
	while (i < size)
	{
		fail_count += (are_same_token(tok_lst->content, exp_tok + i) == false);
		tok_lst = tok_lst->next;
		++i;
	}
	CU_ASSERT_EQUAL(fail_count, 0);
	ft_lstclear(&tmp_lst, free);
}

static void	compare_tok_lst_null(const char *str, const t_token *exp_tok[], const size_t size)
{
	size_t	fail_count;
	t_list	*tok_lst;
	t_list	*tmp_lst;
	size_t	i;

	fail_count = 0;
	tok_lst = lexer_root(str);
	tmp_lst = tok_lst;
	i = 0;
	while (i < size)
	{
		fail_count += (are_same_token(tok_lst->content, exp_tok[i]) == false);
		tok_lst = tok_lst->next;
		++i;
	}
	CU_ASSERT_EQUAL(fail_count, 0);
	ft_lstclear(&tmp_lst, free);
}

void	lexer_root__test(void)
{
	const char				str1[] = "hello";
	static const t_token	tok_lst1[] = {
		{.type = T_GENERIC, .value = "hello"}
	};
	const char				str2[] = "cat wouah | ls";
	static const t_token	tok_lst2[] = {
		{.type = T_GENERIC, .value = "cat"},
		{.type = T_GENERIC, .value = "wouah"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_GENERIC, .value = "ls"}
	};
	const char				str3[] = "";
	const t_token			*tok_lst3[] = {
		NULL
	};
	const char				str4[] = "ls>wouah|cat";
	static const t_token	tok_lst4[] = {
		{.type = T_GENERIC, .value = "ls"},
		{.type = T_RCHEVRON, .value = ">"},
		{.type = T_GENERIC, .value = "wouah"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_GENERIC, .value = "cat"}
	};

	compare_tok_lst(str1, tok_lst1, 1);
	compare_tok_lst(str2, tok_lst2, 4);
	compare_tok_lst_null(str3, tok_lst3, 1);
	compare_tok_lst(str4, tok_lst4, 5);
}
