/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/14 22:15:32 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_binary(t_command *cmd_data, const char *path)
{
	int	pid;

	if (path == NULL)
		print_error("%s: %s\n", cmd_data->command[0], CMD_NOT_FOUND);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, cmd_data->command, cmd_data->env) == -1)
				exit_shell(EXIT_FAILURE);
		}
		else if (pid != -1)
			wait(NULL);
	}
}

void	execution(t_command *command)
{
	char	*path;

	if (is_builtin(command) == true)
		exec_builtin(command);
	else
	{
		if (is_cmd_path(command) == true)
			path = get_path_from_cmd(command);
		else
			path = get_path_from_env(command);
		exec_binary(command, path);
		free(path);
	}
}
