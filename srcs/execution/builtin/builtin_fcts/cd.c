/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/25 14:39:28 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cd(t_command *cmd_data)
{
	static bool		is_print = false;
	char *const		cd_arg = get_cd_arg(cmd_data,
			cmd_data->command[1], &is_print);

	check_pos(CHDIR);
	if (cd_arg != NULL)
	{
		if (chdir(cd_arg) != -1)
		{
			update_cwd_var(cd_arg);
			if (is_print == true)
				print_pos();
		}
		else
		{
			print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, cd_arg);
			perror(EMPTY_STR);
		}
	}
	free(cd_arg);
	is_print = false;
}

void	cd_builtin(t_command *cmd_data)
{
	if (is_correct_size(cmd_data->command) == true)
		execute_cd(cmd_data);
	else
		print_error("%s: %s: %s\n", MINISHELL, CD_BUILTIN, TOO_MANY_ARGS);
}
