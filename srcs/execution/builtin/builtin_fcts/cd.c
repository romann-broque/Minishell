/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/21 23:05:54 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_correct_size(char **command)
{
	size_t	cmd_size;

	cmd_size = 0;
	while (command[cmd_size])
		cmd_size++;
	if (cmd_size > CD_EXP_ARG)
	{
		print_error("%s: %s: %s\n", MINISHELL, CD_BUILTIN, TOO_MANY_ARGS);
		return (false);
	}
	return (true);
}

static char	*get_cd_arg(char *arg)
{
	char	*var_name;
	char	*new_arg;

	new_arg = arg;
	if (arg == NULL || streq(arg, MINUS_SIGN))
	{
		if (arg == NULL)
			var_name = HOME_VAR;
		else if (streq(arg, MINUS_SIGN) == true)
			var_name = OLDPWD_VAR;
		new_arg = ft_getenv(var_name);
		if (new_arg == NULL)
			print_error("%s: %s: %s not set\n", MINISHELL,
				CD_BUILTIN, var_name);
	}
	return (new_arg);
}

static bool	is_prev_option(char **command)
{
	return (command[1] != NULL && streq(command[1], MINUS_SIGN) == true);
}

static void	execute_cd(t_command *cmd_data)
{
	char *const	cd_arg = get_cd_arg(cmd_data->command[1]);

	if (chdir(cd_arg) != -1)
	{
		update_cwd_var();
		if (is_prev_option(cmd_data->command) == true)
			print_pos();
	}
	else if (cd_arg != NULL)
	{
		print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, cd_arg);
		perror(EMPTY_STR);
	}
}

void	cd_builtin(t_command *cmd_data)
{
	if (is_correct_size(cmd_data->command) == true)
		execute_cd(cmd_data);
}
