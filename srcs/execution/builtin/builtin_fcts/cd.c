/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/28 11:02:32 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_chdir_err(char *const cd_arg)
{
	print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, cd_arg);
	perror(EMPTY_STR);
	free(cd_arg);
	return (1);
}

static int	execute_cd(t_command *cmd_data)
{
	static bool		is_print = false;
	char *const		cd_arg = get_cd_arg(cmd_data,
			cmd_data->command[1], &is_print);

	check_pos(CHDIR);
	if (cd_arg == NULL)
		return (1);
	else
	{
		if (chdir(cd_arg) != -1)
		{
			update_cwd_var(cd_arg);
			if (is_print == true)
				print_pos();
		}
		else
			return (handle_chdir_err(cd_arg));
	}
	free(cd_arg);
	is_print = false;
	return (0);
}

int	cd_builtin(t_command *cmd_data)
{
	if (is_correct_size(cmd_data->command) == true)
		return (execute_cd(cmd_data));
	else
	{
		print_error("%s: %s: %s\n", MINISHELL, CD_BUILTIN, TOO_MANY_ARGS);
		return (1);
	}
}
