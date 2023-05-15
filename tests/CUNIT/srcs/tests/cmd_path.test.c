/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 10:34:14 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

extern t_global	g_global;

static void	ASSERT_AND_FREE(char *str1, const char *str2)
{
	CU_ASSERT_STRING_EQUAL(str1, str2);
	free(str1);
}

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
	char	**env_array = dup_env_lst_to_array(g_global.env);

	t_command	cmd1 = {
		.env = env_array,
		.command = (char *[]){
			"ls",
			"-a",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd2 = {
		.env = env_array,
		.command = (char *[]){
			"cat",
			"-e",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd3 = {
		.env = env_array,
		.command = (char *[]){
			"env",
			"-i",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd4 = {
		.env = env_array,
		.command = (char *[]){
			"rev",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd5 = {
		.env = env_array,
		.command = (char *[]){
			"blata",
			"-a",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd6 = {
		.env = env_array,
		.command = (char *[]){
			"awdfoawhd",
			"-a",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd7 = {
		.env = env_array,
		.command = (char *[]){
			"",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	t_command	cmd8 = {
		.env = env_array,
		.command = (char *[]){
			"bonjour",
			"comment",
			"va",
			NULL
			},
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
	};

	str_out_t1 = get_path_from_env(cmd1.command[0], PATH_VAR, cmd1.env);
	ASSERT_AND_FREE(str_out_t1, str_ref_t1);

	str_out_t2 = get_path_from_env(cmd2.command[0], PATH_VAR, cmd2.env);
	ASSERT_AND_FREE(str_out_t2, str_ref_t2);

	str_out_t3 = get_path_from_env(cmd3.command[0], PATH_VAR, cmd3.env);
	ASSERT_AND_FREE(str_out_t3, str_ref_t3);

	str_out_t4 = get_path_from_env(cmd4.command[0], PATH_VAR, cmd4.env);
	ASSERT_AND_FREE(str_out_t4, str_ref_t4);

	str_out_t5 = get_path_from_env(cmd5.command[0], PATH_VAR, cmd5.env);
	CU_ASSERT_PTR_NULL(str_out_t5);

	str_out_t6 = get_path_from_env(cmd6.command[0], PATH_VAR, cmd6.env);
	CU_ASSERT_PTR_NULL(str_out_t6);

	str_out_t7 = get_path_from_env(cmd7.command[0], PATH_VAR, cmd7.env);
	CU_ASSERT_PTR_NULL(str_out_t7);

	str_out_t8 = get_path_from_env(cmd8.command[0], PATH_VAR, cmd8.env);
	CU_ASSERT_PTR_NULL(str_out_t8);

	free_strs(env_array);
}
