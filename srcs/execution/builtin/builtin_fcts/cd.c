/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/05/28 14:38:00 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_chdir_err(const char *const cd_arg)
{
	print_error("%s: %s: %s: %s\n",
		MINISHELL, CD_BUILTIN, cd_arg, strerror(errno));
}

static int	change_dir(const char *arg, const bool is_print)
{
	int	ret_val;

	ret_val = EXIT_FAILURE;
	if (arg[0] == '\0' || chdir(arg) != -1)
	{
		if (arg[0] == '\0')
		{
			ft_printf("%s\n", ft_getenv(OLDPWD_VAR));
			update_cwd_var(arg);
		}
		else
		{
			update_cwd_var(arg);
			if (is_print == true)
				print_pos();
		}
		ret_val = EXIT_SUCCESS;
	}
	else
		handle_chdir_err(arg);
	return (ret_val);
}

static int	execute_cd(t_command *cmd_data)
{
	static bool		is_print = false;
	char *const		cd_arg = get_cd_arg(cmd_data,
			cmd_data->command[1], &is_print);
	int				ret_val;

	ret_val = EXIT_FAILURE;
	check_pos(CHDIR);
	if (cd_arg != NULL)
		ret_val = change_dir(cd_arg, is_print);
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
		return (EXIT_FAILURE);
	}
}
