/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:59 by mat               #+#    #+#             */
/*   Updated: 2023/04/14 11:21:51 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_path(t_command *cmd)
{
	return (is_in_str(cmd->command[0], FWD_SLASH));
}

char	*get_path_from_cmd(t_command *cmd)
{
	return (cmd->command[0]);
}

static char	*get_path_cmd(t_command *cmd, char **path_array)
{
	const char	*cmd_name = cmd->command[0];
	char		*path;
	size_t		i;

	path = NULL;
	i = 0;
	while (path_array[i] != NULL)
	{
		path = ft_strjoin(path_array[i], cmd_name);
		if (path == NULL)
			return (NULL);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

static char	**get_path_var(const char **env)
{
	char	*joint_path;
	char	**path_array;
	size_t	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	joint_path = replace_str(env[i], EMPTY_STR, 0, 5);
	path_array = ft_split(joint_path, COLON);
	if (path_array != NULL)
		add_fwd_slash(&path_array);
	free(joint_path);
	return (path_array);
}

char	*get_path_from_env(t_command *cmd)
{
	char	**path_array;
	char	*path;

	if (is_var_path_in_env(cmd->env) == false || is_empty_cmd(cmd) == true)
		return (NULL);
	path_array = get_path_var(cmd->env);
	if (path_array == NULL)
		return (NULL);
	print_strs((const char **)path_array);
	path = get_path_cmd(cmd, path_array);
	free_strs(path_array);
	return (path);
}
