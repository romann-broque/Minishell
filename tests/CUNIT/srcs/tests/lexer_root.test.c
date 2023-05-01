/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_root.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:12:25 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/29 17:07:00 by rbroque          ###   ########.fr       */
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
	ft_lstclear(&tmp_lst, (void (*)(void *))free_token);
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
	ft_lstclear(&tmp_lst, (void (*)(void *))free_token);
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
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_GENERIC, .value = "wouah"},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_GENERIC, .value = "ls"}
	};
	const char				str3[] = "";
	const t_token			*tok_lst3[] = {
		NULL
	};
	const char				str4[] = "ls>wouah|cat";
	static const t_token	tok_lst4[] = {
		{.type = T_GENERIC, .value = "ls"},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_GENERIC, .value = "wouah"},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_GENERIC, .value = "cat"}
	};
	const char				str5[] = "ls>wouah||cat";
	static const t_token	tok_lst5[] = {
		{.type = T_GENERIC, .value = "ls"},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_GENERIC, .value = "wouah"},
		{.type = T_OR, .value = OR},
		{.type = T_GENERIC, .value = "cat"}
	};
	const char				str6[] = ">>>>>>>|<>|||";
	static const t_token	tok_lst6[] = {
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_LCHEVRON, .value = LCHEVRON},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_OR, .value = OR},
	};
	const char				str7[] = ">>\'wouah\'>>>>\"<wtf>\">|<>|||";
	static const t_token	tok_lst7[] = {
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_QGENERIC, .value = "\'wouah\'"},
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_QGENERIC, .value = "\"<wtf>\""},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_LCHEVRON, .value = LCHEVRON},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_OR, .value = OR},
		{.type = T_PIPE, .value = PIPE},
	};
	const char				str8[] = ">>\'wou<|>ah\'>>\"<w|t|f>\">|<>|||";
	static const t_token	tok_lst8[] = {
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_QGENERIC, .value = "\'wou<|>ah\'"},
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_QGENERIC, .value = "\"<w|t|f>\""},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_LCHEVRON, .value = LCHEVRON},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_OR, .value = OR},
		{.type = T_PIPE, .value = PIPE},
	};
	const char				str9[] = "\"\'wou<|>ah\'\" >< |>>        \"<w|t|f>\">|<>||>|   ";
	static const t_token	tok_lst9[] = {
		{.type = T_QGENERIC, .value = "\"\'wou<|>ah\'\""},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_LCHEVRON, .value = LCHEVRON},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_DOUBLE_RCHEVRON, .value = DOUBLE_RCHEVRON},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_QGENERIC, .value = "\"<w|t|f>\""},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_LCHEVRON, .value = LCHEVRON},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_OR, .value = OR},
		{.type = T_RCHEVRON, .value = RCHEVRON},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_SEPARATOR, .value = SEP},
	};
	const char				str10[] = "    \" &&  \'|   \'\"<\'<>\' \'||\'& ";
	static const t_token	tok_lst10[] = {
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_QGENERIC, .value = "\" &&  \'|   \'\""},
		{.type = T_LCHEVRON, .value = LCHEVRON},
		{.type = T_QGENERIC, .value = "\'<>\'"},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_QGENERIC, .value = "\'||\'"},
		{.type = T_GENERIC, .value = "&"},
		{.type = T_SEPARATOR, .value = SEP},
	};
	const char				str11[] = "&\'wouah\'& ||";
	static const t_token	tok_lst11[] = {
		{.type = T_GENERIC, .value = "&"},
		{.type = T_QGENERIC, .value = "\'wouah\'"},
		{.type = T_GENERIC, .value = "&"},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_OR, .value = OR},
	};
	const char				str12[] = "lol=42&\'wouah\'& ||";
	static const t_token	tok_lst12[] = {
		{.type = T_GENERIC, .value = "lol"},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "42&"},
		{.type = T_QGENERIC, .value = "\'wouah\'"},
		{.type = T_GENERIC, .value = "&"},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_OR, .value = OR},
	};
	const char				str13[] = "=42&\'wouah\'& ||";
	static const t_token	tok_lst13[] = {
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "42&"},
		{.type = T_QGENERIC, .value = "\'wouah\'"},
		{.type = T_GENERIC, .value = "&"},
		{.type = T_SEPARATOR, .value = SEP},
		{.type = T_OR, .value = OR},
	};
	const char				str14[] = "lol=4=2";
	static const t_token	tok_lst14[] = {
		{.type = T_GENERIC, .value = "lol"},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "4"},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "2"},
	};
	const char				str15[] = "lol==42";
	static const t_token	tok_lst15[] = {
		{.type = T_GENERIC, .value = "lol"},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "42"},
	};
	const char				str16[] = "=42";
	static const t_token	tok_lst16[] = {
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "42"},
	};
	const char				str17[] = "=";
	static const t_token	tok_lst17[] = {
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
	};
	const char				str18[] = "\'lol=42\'";
	static const t_token	tok_lst18[] = {
		{.type = T_QGENERIC, .value = "\'lol=42\'"},
	};
	const char				str19[] = "lol=\"\'lol=42\'\"";
	static const t_token	tok_lst19[] = {
		{.type = T_GENERIC, .value = "lol"},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_QGENERIC, .value = "\"\'lol=42\'\""},
	};
	const char				str20[] = "===";
	static const t_token	tok_lst20[] = {
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
	};
	const char				str21[] = "\"=\"==42";
	static const t_token	tok_lst21[] = {
		{.type = T_QGENERIC, .value = "\"=\""},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_ASSIGN, .value = ASSIGN_EQ},
		{.type = T_GENERIC, .value = "42"},
	};
	const char				str22[] = "\"=\"\'==42\'";
	static const t_token	tok_lst22[] = {
		{.type = T_QGENERIC, .value = "\"=\""},
		{.type = T_QGENERIC, .value = "\'==42\'"},
	};

	compare_tok_lst(str1, tok_lst1, 1);
	compare_tok_lst(str2, tok_lst2, 7);
	compare_tok_lst_null(str3, tok_lst3, 1);
	compare_tok_lst(str4, tok_lst4, 5);
	compare_tok_lst(str5, tok_lst5, 5);
	compare_tok_lst(str6, tok_lst6, 8);
	compare_tok_lst(str7, tok_lst7, 11);
	compare_tok_lst(str8, tok_lst8, 10);
	compare_tok_lst(str9, tok_lst9, 17);
	compare_tok_lst(str10, tok_lst10, 8);
	compare_tok_lst(str11, tok_lst11, 5);
	compare_tok_lst(str12, tok_lst12, 7);
	compare_tok_lst(str13, tok_lst13, 6);
	compare_tok_lst(str14, tok_lst14, 5);
	compare_tok_lst(str15, tok_lst15, 3);
	compare_tok_lst(str16, tok_lst16, 2);
	compare_tok_lst(str17, tok_lst17, 1);
	compare_tok_lst(str18, tok_lst18, 1);
	compare_tok_lst(str19, tok_lst19, 3);
	compare_tok_lst(str20, tok_lst20, 3);
	compare_tok_lst(str21, tok_lst21, 4);
	compare_tok_lst(str22, tok_lst22, 2);
}
