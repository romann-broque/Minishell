/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:38:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/19 09:52:27 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	call_builtin(const t_builtin_mapper *map, t_command *cmd_data)
{
	const char	*cmd_name = cmd_data->command[0];
	size_t		i;

	i = 0;
	while (map[i].name != NULL)
	{
		if (streq(map[i].name, cmd_name) == true)
			break ;
		++i;
	}
	if (map[i].fct != NULL)
		map[i].fct(cmd_data->command);
}

void	exec_builtin(t_command *command)
{
	static const t_builtin_mapper	map[] = {
	{.name = CD_BUILTIN, .fct = cd_builtin},
	{.name = ECHO_BUILTIN, .fct = NULL},
	{.name = EXIT_BUILTIN, .fct = exit_builtin},
	{.name = EXPORT_BUILTIN, .fct = NULL},
	{.name = PWD_BUILTIN, .fct = pwd_builtin},
	{.name = UNSET_BUILTIN, .fct = NULL},
	{NULL, NULL},
	};

	call_builtin(map, command);
}
