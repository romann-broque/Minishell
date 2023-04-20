/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:48:00 by mat               #+#    #+#             */
/*   Updated: 2023/04/20 14:10:54 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

t_list	*get_list_from_array(t_token *tab)
{
	size_t	i;
	t_list	*tokens_list;

	tokens_list = NULL;
	i = 0;
	while (tab[i].type != T_END)
	{
		ft_lstadd_back(&tokens_list, ft_lstnew(tab + i));
		i++;
	}
	ft_lstadd_back(&tokens_list, ft_lstnew(tab + i));
	return (tokens_list);
}

void	print_list(t_list *toks)
{
	while (toks)
	{
		if (toks->content)
		{
			printf("-----\n");
			printf("tok type is %u\n", get_type_from_tok(toks->content));
			printf("tok value is %s\n", get_str_from_tok(toks->content));
			printf("-----\n");
		}
		toks = toks->next;
	}
}

void	parser__test(void)
{
	t_list	*tokens_test1;
	t_list	*tokens_test2;
	t_list	*tokens_test3;
	t_list	*tokens_test4;
	t_list	*tokens_test5;
	t_list	*tokens_test6;
	t_list	*tokens_test7;
	t_list	*tokens_test8;
	t_list	*tokens_test9;
	t_list	*tokens_test10;
	t_list	*tokens_test11;
	t_list	*tokens_test12;
	t_list	*tokens_test13;



	t_token	t_1_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "hola"},
		{.type = T_GENERIC, .value = "commo"},
		{.type = T_GENERIC, .value = "esta"},
		{.type = T_END, .value = NULL}
	};

	tokens_test1 = get_list_from_array(t_1_toks);
	CU_ASSERT_EQUAL(parser(tokens_test1), true);
	ft_lstclear(&tokens_test1, NULL);

	t_token	t_2_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "Heyo"},
		{.type = T_RCHEVRON, .value = ">"},
		{.type = T_GENERIC, .value = "blata"},
		{.type = T_END, .value = NULL}
	};

	tokens_test2 = get_list_from_array(t_2_toks);
	CU_ASSERT_TRUE(parser(tokens_test2));
	ft_lstclear(&tokens_test2, NULL);

	t_token	t_3_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "blata"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_RCHEVRON, .value = ">"},
		{.type = T_END, .value = NULL}
	};

	tokens_test3 = get_list_from_array(t_3_toks);
	CU_ASSERT_FALSE(parser(tokens_test3));
	ft_lstclear(&tokens_test3, NULL);

	t_token	t_4_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_END, .value = NULL}
	};

	tokens_test4 = get_list_from_array(t_4_toks);
	CU_ASSERT_FALSE(parser(tokens_test4));
	ft_lstclear(&tokens_test4, NULL);

	t_token	t_5_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_GENERIC, .value = "blata"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_END, .value = NULL}
	};

	tokens_test5 = get_list_from_array(t_5_toks);
	CU_ASSERT_FALSE(parser(tokens_test5));
	ft_lstclear(&tokens_test5, NULL);

	t_token	t_6_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_AND, .value = "&&"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_END, .value = NULL}
	};

	tokens_test6 = get_list_from_array(t_6_toks);
	CU_ASSERT_FALSE(parser(tokens_test6));
	ft_lstclear(&tokens_test6, NULL);

	t_token	t_7_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_GENERIC, .value = "BLATA"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_END, .value = NULL}
	};

	tokens_test7 = get_list_from_array(t_7_toks);
	CU_ASSERT_FALSE(parser(tokens_test7));
	ft_lstclear(&tokens_test7, NULL);

	t_token	t_8_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_GENERIC, .value = "BLATA"},
		{.type = T_ASSIGN, .value = "BLA=54"},
		{.type = T_END, .value = NULL}
	};
	tokens_test8 = get_list_from_array(t_8_toks);
	CU_ASSERT_TRUE(parser(tokens_test8));
	ft_lstclear(&tokens_test8, NULL);

	t_token	t_9_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_PIPE, .value = "|"},
		{.type = T_END, .value = NULL}
	};

	tokens_test9 = get_list_from_array(t_9_toks);
	CU_ASSERT_FALSE(parser(tokens_test9));
	ft_lstclear(&tokens_test9, NULL);

	t_token	t_10_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_END, .value = NULL}
	};

	tokens_test10 = get_list_from_array(t_10_toks);
	CU_ASSERT_TRUE(parser(tokens_test10));
	ft_lstclear(&tokens_test10, NULL);

	t_token	t_11_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_GENERIC, .value = "arg"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_GENERIC, .value = "BLATA"},
		{.type = T_LCHEVRON, .value = "<"},
		{.type = T_ASSIGN, .value = "ASSIGN"},
		{.type = T_END, .value = NULL}
	};

	tokens_test11 = get_list_from_array(t_11_toks);
	CU_ASSERT_TRUE(parser(tokens_test11));
	ft_lstclear(&tokens_test11, NULL);

	t_token	t_12_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "bonjour"},
		{.type = T_PIPE, .value = "|"},
		{.type = T_DOUBLE_LCHEVRON, .value = "<<"},
		{.type = T_GENERIC, .value = "RAGE AGAINST THE MACHINE"},
		{.type = T_END, .value = NULL}
	};

	tokens_test12 = get_list_from_array(t_12_toks);
	CU_ASSERT_TRUE(parser(tokens_test12));
	ft_lstclear(&tokens_test12, NULL);

	t_token	t_13_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_END, .value = NULL}
	};

	tokens_test13 = get_list_from_array(t_13_toks);
	CU_ASSERT_TRUE(parser(tokens_test13));
	ft_lstclear(&tokens_test13, NULL);
}
