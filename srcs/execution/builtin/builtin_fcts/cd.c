/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/05/01 10:26:16 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_chdir_err(char *const cd_arg)
{
	print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, cd_arg);
	perror(EMPTY_STR);
	return (1);
}

static int	execute_cd(t_command *cmd_data)
{
	static bool		is_print = false;
	char *const		cd_arg = get_cd_arg(cmd_data,
			cmd_data->command[1], &is_print);
	int				ret_val;

	ret_val = 0;
	check_pos(CHDIR);
	if (cd_arg == NULL)
		ret_val = 1;
	else
	{
		if (chdir(cd_arg) != -1)
		{
			update_cwd_var(cd_arg);
			if (is_print == true)
				print_pos();
		}
		else
			ret_val = handle_chdir_err(cd_arg);
	}
	free(cd_arg);
	is_print = false;
	return (ret_val);
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
