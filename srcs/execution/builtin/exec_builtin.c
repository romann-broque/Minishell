/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:38:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/15 16:50:26 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	call_builtin(const t_builtin_mapper *map, t_command *cmd_data)
{
	const char	*cmd_name = cmd_data->command[0];
	size_t		i;

	i = 0;
	dup_files(cmd_data->fdin, cmd_data->fdout);
	while (map[i].name != NULL)
	{
		if (streq(map[i].name, cmd_name) == true)
			break ;
		++i;
	}
	if (map[i].fct != NULL)
		return (map[i].fct(cmd_data));
	return (EXIT_FAILURE);
}

void	exec_builtin(t_command *command)
{
	static const t_builtin_mapper	map[] = {
	{.name = CD_BUILTIN, .fct = cd_builtin},
	{.name = ECHO_BUILTIN, .fct = echo_builtin},
	{.name = EXIT_BUILTIN, .fct = exit_builtin},
	{.name = EXPORT_BUILTIN, .fct = export_builtin},
	{.name = PWD_BUILTIN, .fct = pwd_builtin},
	{.name = UNSET_BUILTIN, .fct = unset_builtin},
	{.name = ENV_BUILTIN, .fct = env_builtin},
	{NULL, NULL}
	};
	int								pid;

	pid = fork();
	if (pid == 0)
	{
		if (streq(EXIT_BUILTIN, command->command[0]) == false)
			g_global.last_ret_val = call_builtin(map, command);
		exit_shell(g_global.last_ret_val, false);
	}
	else if (pid > 0)
	{
		wait(NULL);
		if (streq(EXIT_BUILTIN, command->command[0]) == true)
			g_global.last_ret_val = call_builtin(map, command);
	}
}
