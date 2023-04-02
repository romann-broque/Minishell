/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:28:05 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 00:51:28 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

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
		{.suite=NULL, .sname="Quotes", .tests={
			{.tname="are_quotes_closed", are_quotes_closed__test},
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
