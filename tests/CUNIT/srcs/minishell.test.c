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

t_global	g_global;

void	set_tests(void)
{
	static t_suite	suite_mapping[] = {
		{.suite = NULL, .sname = "Syntax", .tests = {
			{.tname = "are_quotes_closed", are_quotes_closed__test},
			},
		},
		{.suite = NULL, .sname = "Lexer", .tests = {
			{.tname = "get_words", get_words__test},
			{.tname = "lexer_root", lexer_root__test}
			}
		},
		{.suite = NULL, .sname = "Parser", .tests = {
			{.tname = "parser", parser__test}
			}
		},
		{
			.suite = NULL, .sname = "Expand", .tests = {
				{.tname = "expand", expand__test},
			}
		},
		{.suite = NULL, .sname = "Interpreter", .tests = {
			{.tname = "interpreter", interpreter__test}
			}
		},
		{.suite = NULL, .sname = "Execution", .tests = {
			{.tname = "cmd_path", cmd_path__test}
			}
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
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	// Cleanup the CUnit test registry
	exit_tests();
}

int	main(
	__attribute__((unused))int ac,
	__attribute__((unused))char **av,
	char **env)
{
	init_env(&g_global, env);
	exec_tests();
}
