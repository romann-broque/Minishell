/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:54:34 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 13:56:30 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_path(t_command *cmd)
{
	const char	*cmd_name = cmd->command[0];

	return (is_in_str(cmd_name, FWD_SLASH));
}

static void	print_access_error(const char *cmd_name)
{
	const int	errno_tmp = errno;

	print_error("%s: %s: %s\n",
		MINISHELL, cmd_name, strerror(errno_tmp));
	if (errno_tmp == ENOENT)
		update_error_val(NO_FILE);
	else
		update_error_val(NO_ACCESS);
}

char	*get_cmd_path(t_command *cmd_data)
{
	char	*path;

	path = dup_path_from_cmd(cmd_data);
	if (path == NULL)
	{
		print_error("%s: %s: %s\n",
			MINISHELL, cmd_data->command[0], strerror(errno));
		update_error_val(NO_FILE);
	}
	else if (is_cmd_accessible(path) == false)
	{
		print_access_error(cmd_data->command[0]);
		free(path);
		path = NULL;
	}
	return (path);
}
