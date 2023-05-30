/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:38:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 17:49:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	*g_global;

static int	call_builtin(const t_builtin_mapper *map, t_command *cmd_data)
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
		return (map[i].fct(cmd_data));
	return (EXIT_FAILURE);
}

int	exec_builtin(t_command *cmd_data)
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
	int								ret_val;

	update_signal_state(S_EXEC);
	ret_val = call_builtin(map, cmd_data);
	update_signal_state(S_SLEEP);
	return (ret_val);
}
