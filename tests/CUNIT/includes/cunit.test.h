/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cunit.test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:44:31 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 00:59:17 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUNIT_TEST_H
# define CUNIT_TEST_H

# include "minishell.h"
# include <CUnit/CUnit.h>
# include <CUnit/Basic.h>

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

// test_utils.test.c

void	map_suite(t_suite suite_mapping[]);
void	exit_tests(void);

#endif
