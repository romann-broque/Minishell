/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/22 19:48:34 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// chdir is not always going to the wanted folder (if it's a symbolic link)

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
			if (is_print == true)
				print_pos();
			update_cwd_var();
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
}
