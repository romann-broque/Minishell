/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:28:05 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 00:26:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>

int	maxi(const int a, const int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	mini(const int a, const int b)
{
	if (a > b)
		return (b);
	return (a);
}

////////////////////////////////////
//////////// TEST UTILS ////////////
////////////////////////////////////

#define MAX_TESTS_COUNT 10

typedef struct s_test
{
	char	*tname;
	void	(*fct)(void);
}				t_test;

typedef struct s_suite
{
	CU_pSuite suite;
	char	*sname;
	t_test	tests[MAX_TESTS_COUNT];
}				t_suite;

void	test_maxi(void)
{
	CU_ASSERT_FATAL(maxi(0, -2) == 0);
	CU_ASSERT_FATAL(maxi(1, -2) == 1);
	CU_ASSERT_FATAL(maxi(0, 0) == 0);
}

void	test_mini(void)
{
	CU_ASSERT_FATAL(mini(0, -2) == -2);
	CU_ASSERT_FATAL(mini(1, -2) == -2);
	CU_ASSERT_FATAL(mini(0, 0) == 0);
}

bool	are_suites_allocated(t_suite array[])
{
	size_t	i;

	i = 0;
	while (array[i].sname != NULL && array[i].suite != NULL)
		++i;
	return (array[i].sname == NULL && array[i].suite == NULL);
}

void	exit_tests(void)
{
	CU_cleanup_registry();
	exit(CU_get_error());
}

void	add_suites(t_suite suite_mapping[])
{
	size_t	i;

	i = 0;
	while (suite_mapping[i].sname != NULL)
	{
		suite_mapping[i].suite = CU_add_suite(suite_mapping[i].sname, NULL, NULL);
		++i;
	}
}

void	add_tests(t_suite suite_mapping[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (suite_mapping[i].sname != NULL)
	{
		j = 0;
		while (suite_mapping[i].tests[j].tname != NULL)
		{
			if (CU_add_test(
					suite_mapping[i].suite,
					suite_mapping[i].tests[j].tname,
					suite_mapping[i].tests[j].fct)
				== NULL)
				exit_tests();
			++j;
		}
		++i;
	}
}

void	map_suite(t_suite suite_mapping[])
{
	add_suites(suite_mapping);
	if (are_suites_allocated(suite_mapping) == false)
		exit_tests();
	add_tests(suite_mapping);
}

void	set_tests(void)
{
	t_suite	suite_mapping[] = {
		{.suite=NULL, .sname="maxi_suite", .tests={
			{.tname="test_maxi", test_maxi}
			}
		},
		{.suite=NULL, .sname="mini_suite", .tests={
			{.tname="test_mini", test_mini},
			}
		},
		{.suite=NULL, .sname="hybride_suite", .tests={
			{.tname="test_maxi", test_maxi},
			{.tname="test_mini", test_mini},
			}
		},
		{.suite=NULL, .sname=NULL}
	};
	map_suite(suite_mapping);
}

void	exec_tests(void)
{
	// Initialize the CUnit test registry
	if (CU_initialize_registry() != CUE_SUCCESS)
		exit_tests();
	set_tests();
	// Run the tests using the basic test runner
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	// Cleanup the CUnit test registry
	exit_tests();
}

int	main(void)
{
	exec_tests();
}
