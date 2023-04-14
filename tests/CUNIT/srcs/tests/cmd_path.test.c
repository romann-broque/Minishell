/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:11 by mat               #+#    #+#             */
/*   Updated: 2023/04/13 16:16:46 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

extern const char	**g_env;

void	cmd_path__test(void)
{
	const char	*str_ref_t1 = "/usr/bin/ls";
	const char	*str_ref_t2 = "/usr/bin/cat";
	const char	*str_ref_t3 = "/usr/bin/env";
	const char	*str_ref_t4 = "/usr/bin/rev";

	char *str_out_t1;
	char *str_out_t2;
	char *str_out_t3;
	char *str_out_t4;
	char *str_out_t5;
	char *str_out_t6;
	char *str_out_t7;
	char *str_out_t8;

	t_command	cmd1 = {
		.env = g_env,
		.command = (char *[]){
			"ls",
			"-a",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd2 = {
		.env = g_env,
		.command = (char *[]){
			"cat",
			"-e",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd3 = {
		.env = g_env,
		.command = (char *[]){
			"env",
			"-i",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd4 = {
		.env = g_env,
		.command = (char *[]){
			"rev",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd5 = {
		.env = g_env,
		.command = (char *[]){
			"blata",
			"-a",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd6 = {
		.env = g_env,
		.command = (char *[]){
			"awdfoawhd",
			"-a",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd7 = {
		.env = g_env,
		.command = (char *[]){
			"",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd8 = {
		.env = g_env,
		.command = (char *[]){
			"bonjour",
			"comment",
			"va",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	str_out_t1 = get_path_from_env(&cmd1);
	ASSERT_AND_FREE(str_out_t1, str_ref_t1);

	str_out_t2 = get_path_from_env(&cmd2);
	ASSERT_AND_FREE(str_out_t2, str_ref_t2);

	str_out_t3 = get_path_from_env(&cmd3);
	ASSERT_AND_FREE(str_out_t3, str_ref_t3);

	str_out_t4 = get_path_from_env(&cmd4);
	ASSERT_AND_FREE(str_out_t4, str_ref_t4);

	str_out_t5 = get_path_from_env(&cmd5);
	CU_ASSERT_PTR_NULL(str_out_t5);

	str_out_t6 = get_path_from_env(&cmd6);
	CU_ASSERT_PTR_NULL(str_out_t6);

	str_out_t7 = get_path_from_env(&cmd7);
	CU_ASSERT_PTR_NULL(str_out_t7);

	str_out_t8 = get_path_from_env(&cmd8);
	CU_ASSERT_PTR_NULL(str_out_t8);

}
