/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:35:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 14:54:39 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

#define MAX_TOKEN_LEN 30

static void	compare_tok_lst(const char *str, const char exp_tok[][MAX_TOKEN_LEN + 1], const size_t size)
{
	size_t	fail_count;
	t_list	*tok_lst;
	char	**ret_tok;
	size_t	i;

	fail_count = 0;
	tok_lst = get_tokens(str);
	ret_tok = dup_strs_from_lst(tok_lst);
	i = 0;
	while (i < size)
	{
		fail_count += (streq(ret_tok[i], exp_tok[i]) == false);
		++i;
	}
	CU_ASSERT_EQUAL(fail_count, 0);
	ft_lstclear(&tok_lst, free);
	free_strs(ret_tok);
}

static void	compare_tok_lst_ptr(const char *str, const char *exp_tok[], const size_t size)
{
	size_t	fail_count;
	t_list	*tok_lst;
	char	**ret_tok;
	size_t	i;

	fail_count = 0;
	tok_lst = get_tokens(str);
	ret_tok = dup_strs_from_lst(tok_lst);
	i = 0;
	while (i < size)
	{
		fail_count += (ret_tok[i] != exp_tok[i]);
		++i;
	}
	CU_ASSERT_EQUAL(fail_count, 0);
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
	const char		*str2 = "\"hello my friend\"";
	const char		exp_tok2[][MAX_TOKEN_LEN + 1] = {
		"\"hello my friend\""
	};
	const char		*str3 = "\"hello \'my friend\"";
	const char		exp_tok3[][MAX_TOKEN_LEN + 1] = {
		"\"hello \'my friend\""
	};
	const char		*str4 = "\"hello \'my friend\"";
	const char		exp_tok4[][MAX_TOKEN_LEN + 1] = {
		"\"hello \'my friend\""
	};
	const char		*str5 = "\"hello \'my \'friend\"";
	const char		exp_tok5[][MAX_TOKEN_LEN + 1] = {
		"\"hello \'my \'friend\""
	};
	const char		*str6 = "\"hello \'my \'friend\"close";
	const char		exp_tok6[][MAX_TOKEN_LEN + 1] = {
		"\"hello \'my \'friend\"close"
	};
	const char		*str7 = "\"hello \'my \'friend\" close";
	const char		exp_tok7[][MAX_TOKEN_LEN + 1] = {
		"\"hello \'my \'friend\"",
		"close"
	};
	const char		*str8 = "ech\"o\"";
	const char		exp_tok8[][MAX_TOKEN_LEN + 1] = {
		"ech\"o\"",
	};
	const char		*str9 = "\"\"";
	const char		exp_tok9[][MAX_TOKEN_LEN + 1] = {
		"\"\"",
	};
	const char		*str10 = "ec\"ho\" he\"l\"lo";
	const char		exp_tok10[][MAX_TOKEN_LEN + 1] = {
		"ec\"ho\"",
		"he\"l\"lo",
	};
	const char		*str11 = "ec\"ho\" he\'\"\'l\"lo\"";
	const char		exp_tok11[][MAX_TOKEN_LEN + 1] = {
		"ec\"ho\"",
		"he\'\"\'l\"lo\"",
	};
	const char		*str12 = "    hey les   \"\"  \'  \'\'\'         amis";
	const char		exp_tok12[][MAX_TOKEN_LEN + 1] = {
		"hey",
		"les",
		"\"\"",
		"\'  \'\'\'",
		"amis"
	};
	const char		*str13 = "";
	const char		*exp_tok13[] = {NULL};

	const char		*str14 = "             ";
	const char		*exp_tok14[] = {NULL};
	
	const char		*str15 = "echo \"\"\" \"";
	const char		exp_tok15[][MAX_TOKEN_LEN + 1] = {
		"echo",
		"\"\"\" \""
	};
	const char		*str16 = "      he\"l\"   \"o\" ";
	const char		exp_tok16[][MAX_TOKEN_LEN + 1] = {
		"he\"l\"",
		"\"o\""
	};
	const char		*str17 = "\"hel \"   \" lo\"";
	const char		exp_tok17[][MAX_TOKEN_LEN + 1] = {
		"\"hel \"",
		"\" lo\""
	};
	const char		*str18 = "\"hel \"   \" lo\"  ";
	const char		exp_tok18[][MAX_TOKEN_LEN + 1] = {
		"\"hel \"",
		"\" lo\""
	};
	const char		*str19 = "hel\" \' \'\"lo";
	const char		exp_tok19[][MAX_TOKEN_LEN + 1] = {
		"hel\" \' \'\"lo",
	};
	const char		*str20 = "\"\'\" \"\"";
	const char		exp_tok20[][MAX_TOKEN_LEN + 1] = {
		"\"\'\"",
		"\"\"",
	};
	const char		*str21 = "\"\'\'\'\" \"\" \"\'\'\'\'\"";
	const char		exp_tok21[][MAX_TOKEN_LEN + 1] = {
		"\"\'\'\'\"",
		"\"\"",
		"\"\'\'\'\'\""
	};
	const char		*str22 = "      po\"u\'e\'t\" o\'k\'\'\' t\"\"\"rop r\'igo\'lo ce \"test\"\"    ";
	const char		exp_tok22[][MAX_TOKEN_LEN + 1] = {
		"po\"u\'e\'t\"",
		"o\'k\'\'\'",
		"t\"\"\"rop r\'igo\'lo ce \"test\"\""
	};


	compare_tok_lst(str1, exp_tok1, 3);
	compare_tok_lst(str2, exp_tok2, 1);
	compare_tok_lst(str3, exp_tok3, 1);
	compare_tok_lst(str4, exp_tok4, 1);
	compare_tok_lst(str5, exp_tok5, 1);
	compare_tok_lst(str6, exp_tok6, 1);
	compare_tok_lst(str7, exp_tok7, 2);
	compare_tok_lst(str8, exp_tok8, 1);
	compare_tok_lst(str9, exp_tok9, 1);
	compare_tok_lst(str10, exp_tok10, 2);
	compare_tok_lst(str11, exp_tok11, 2);
	compare_tok_lst(str12, exp_tok12, 5);
	compare_tok_lst_ptr(str13, exp_tok13, 1);
	compare_tok_lst_ptr(str14, exp_tok14, 1);
	compare_tok_lst(str15, exp_tok15, 2);
	compare_tok_lst(str16, exp_tok16, 2);
	compare_tok_lst(str17, exp_tok17, 2);
	compare_tok_lst(str18, exp_tok18, 2);
	compare_tok_lst(str19, exp_tok19, 1);
	compare_tok_lst(str20, exp_tok20, 2);
	compare_tok_lst(str21, exp_tok21, 3);
	compare_tok_lst(str22, exp_tok22, 3);
}
