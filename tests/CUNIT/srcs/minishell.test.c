/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:28:05 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 14:52:12 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	set_tests(void)
{
	static t_suite	suite_mapping[] = {
		{.suite = NULL, .sname = "Quotes", .tests = {
			{.tname = "are_quotes_closed", are_quotes_closed__test},
			},
		},
		{.suite = NULL, .sname = NULL}
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
