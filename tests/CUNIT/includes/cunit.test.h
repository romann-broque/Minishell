/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cunit.test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:44:31 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 11:49:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUNIT_TEST_H
# define CUNIT_TEST_H

# include "minishell.h"
# include <CUnit/CUnit.h>
# include <CUnit/Basic.h>

# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define MAX_TESTS_COUNT 10

typedef struct s_test
{
	char	*tname;
	void	(*fct)(void);
}				t_test;

typedef struct s_suite
{
	CU_pSuite	suite;
	char		*sname;
	t_test		tests[MAX_TESTS_COUNT];
}				t_suite;

// are_quotes_closed.test.c

void	are_quotes_closed__test(void);

// get_token.test.c

void	get_token__test(void);

//// UTILS ////

// test_utils.test.c

void	map_suite(t_suite suite_mapping[]);
void	exit_tests(void);

// list_test.test.c

char	**dup_strs_from_lst(t_list *lst);

#endif
