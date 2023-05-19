/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:38:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/19 09:54:03 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	call_builtin(
	const t_builtin_mapper *map,
	t_command *cmd_data,
	int *end
	)
{
	const char	*cmd_name = cmd_data->command[0];
	size_t		i;

	i = 0;
	dup_child(cmd_data, end);
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

static void	close_builtin(t_command *cmd_data, int *end)
{
	close(end[1]);
	if (g_global.cmd_nbr > 1 && cmd_data->index > 1)
		close(g_global.prev_pipe);
	if (cmd_data->index == g_global.cmd_nbr)
		close(end[0]);
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
	int								end[2];

	pipe(end);
	g_global.last_ret_val = call_builtin(map, command, end);
	close_builtin(command, end);
	dup2(g_global.stdin, STDIN_FILENO);
	dup2(g_global.stdout, STDOUT_FILENO);
	g_global.prev_pipe = end[0];
}
