/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/20 16:44:46 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_correct_size(char **command)
{
	size_t	cmd_size;

	cmd_size = 0;
	while (command[cmd_size])
		cmd_size++;
	if (cmd_size > 2)
	{
		print_error("%s: %s: %s\n", MINISHELL, CD_BUILTIN, TOO_MANY_ARGS);
		return (false);
	}
	return (true);
}

static void	exec_spec_cd(char *var_name)
{
	const char	*var_value = getenv(var_name);

	if (var_value == NULL)
		print_error("%s: %s: %s not set\n", MINISHELL, CD_BUILTIN, var_name);
	chdir(var_value);
}

static void	cd_spec(char *arg)
{
	char	*var_name;

	if (arg != NULL)
		var_name = "OLDPWD";
	else
		var_name = "HOME";
	exec_spec_cd(var_name);
}

static void	execute_cd(char *arg)
{
	if (arg == NULL || ft_strcmp(MINUS_SIGN, arg) == 0)
		cd_spec(arg);
	else if (chdir(arg) == -1)
	{
		print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, arg);
		perror(EMPTY_STR);
	}
}

void	cd_builtin(char **command)
{
	if (is_correct_size(command) == true)
		execute_cd(command[1]);
}
