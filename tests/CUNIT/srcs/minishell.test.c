/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:28:05 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 14:52:1t p2 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	set_tests(void)
{
	static t_suite	suite_mapping[] = {
		{.suite = NULL, .sname = "Syntax", .tests = {
			{.tname = "are_quotes_closed", are_quotes_closed__test},
			},
		},
		{.suite = NULL, .sname = "Lexer", .tests = {
			{.tname = "get_words", get_words__test},
			{.tname = "lexer_root", lexer_root__test},
			},
		},
		{
			.suite = NULL, .sname = "Expand", .tests = {
				{.tname = "expand_var", expand_var__test},
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
	CU_set_error_action(CUEA_IGNORE);

	// Run the tests using the basic test runner
	CU_basic_set_mode(CU_BRM_NORMAL);
	CU_basic_run_tests();

	// Cleanup the CUnit test registry
	exit_tests();
}

int	main(void)
{
	exec_tests();
}
