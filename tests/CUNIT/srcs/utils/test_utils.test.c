/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:43:02 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 11:49:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

static bool	are_suites_allocated(t_suite array[])
{
	size_t	i;

	i = 0;
	while (array[i].sname != NULL && array[i].suite != NULL)
		++i;
	return (array[i].sname == NULL && array[i].suite == NULL);
}

static void	add_suites(t_suite suite_mapping[])
{
	size_t	i;

	i = 0;
	while (suite_mapping[i].sname != NULL)
	{
		suite_mapping[i].suite = CU_add_suite(suite_mapping[i].sname, NULL, NULL);
		++i;
	}
}

static void	add_tests(t_suite suite_mapping[])
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

void	exit_tests(void)
{
	const int	exit_value = (CU_get_error() || (CU_get_number_of_failures() > 0));

	CU_cleanup_registry();
	if (exit_value == 0)
		dprintf(STDERR_FILENO, ANSI_COLOR_GREEN "OK\n" ANSI_COLOR_RESET);
	else
		dprintf(STDERR_FILENO, ANSI_COLOR_RED "KO\n" ANSI_COLOR_RESET);
	exit(exit_value);
}
