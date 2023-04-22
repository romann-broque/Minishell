/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/22 18:13:55 by rbroque          ###   ########.fr       */
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

static char	*get_cd_arg(t_command *cmd_data, char *arg)
{
	char	*var_name;
	char	*new_arg;

	if (arg == NULL || streq(arg, TIELD) || streq(arg, MINUS_SIGN))
	{
		if (arg == NULL || streq(arg, TIELD))
			var_name = HOME_VAR;
		else if (streq(arg, MINUS_SIGN) == true)
			var_name = OLDPWD_VAR;
		new_arg = ft_strdup(ft_getenv(var_name));
		if (new_arg == NULL)
			print_error("%s: %s: %s not set\n", MINISHELL,
				CD_BUILTIN, var_name);
		return (new_arg);
	}
	if (arg != NULL && arg[0] != '/' && arg[0] != '.' )
	{
		new_arg = get_path_from_env(arg, CDPATH_VAR, cmd_data->env);
		if (new_arg != NULL)
		{
			printf("%s\n", new_arg);
			return (new_arg);
		}
	}
	return (ft_strdup(arg));
}

static bool	is_prev_option(char **command)
{
	return (command[1] != NULL && streq(command[1], MINUS_SIGN) == true);
}

static void	execute_cd(t_command *cmd_data)
{
	char *const	cd_arg = get_cd_arg(cmd_data, cmd_data->command[1]);

	check_pos(CHDIR);
	if (cd_arg != NULL)
	{
		if (chdir(cd_arg) != -1)
		{
			update_cwd_var();
			if (is_prev_option(cmd_data->command) == true)
				print_pos();
		}
		else
		{
			print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, cd_arg);
			perror(EMPTY_STR);
		}
	}
	free(cd_arg);
}

void	cd_builtin(t_command *cmd_data)
{
	if (is_correct_size(cmd_data->command) == true)
		execute_cd(cmd_data);
}
