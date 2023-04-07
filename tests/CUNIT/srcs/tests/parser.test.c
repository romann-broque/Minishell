/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:48:00 by mat               #+#    #+#             */
/*   Updated: 2023/04/07 11:13:09 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

t_list	*get_list_from_tab(t_token *tab)
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


static t_toktype	get_type_from_tok(t_token *tok)
{
	return (tok->type);
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
	//t_list	*tokens_test6;
	//t_list	*tokens_test7;
	//t_list	*tokens_test8;
	//t_list	*tokens_test9;
	//t_list	*tokens_test10;
	//t_list	*tokens_test11;
	//t_list	*tokens_test12;



	t_token	t_1_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "hola"},
		{.type = T_GENERIC, .value = "commo"},
		{.type = T_GENERIC, .value = "esta"},
		{.type = T_END, .value = NULL}
	};

	tokens_test1 = get_list_from_tab(t_1_toks);
	CU_ASSERT_EQUAL(parser(tokens_test1), true);
	ft_lstclear(&tokens_test1, NULL);

	t_token	t_2_toks[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "Heyo"},
		{.type = T_RCHEVRON, .value = ">"},
		{.type = T_GENERIC, .value = "blata"},
		{.type = T_END, .value = NULL}
	};

	tokens_test2 = get_list_from_tab(t_2_toks);
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

	tokens_test3 = get_list_from_tab(t_3_toks);
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

	tokens_test4 = get_list_from_tab(t_4_toks);
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

	tokens_test5 = get_list_from_tab(t_5_toks);
	CU_ASSERT_FALSE(parser(tokens_test5));
	ft_lstclear(&tokens_test5, NULL);

}
