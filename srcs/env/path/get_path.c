/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:59 by mat               #+#    #+#             */
/*   Updated: 2023/05/28 13:17:53 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_path(t_command *cmd)
{
	return (is_in_str(cmd->command[0], FWD_SLASH));
}

char	*get_cmd_path(t_command *cmd_data)
{
	char	*path;

	path = dup_path_from_cmd(cmd_data);
	if (path == NULL || is_cmd_accessible(path) == false)
	{
		print_error("%s: %s: %s\n",
			MINISHELL, cmd_data->command[0], strerror(errno));
		if (path == NULL)
			update_error_val(NO_FILE);
		else
		{
			update_error_val(NO_ACCESS);
			free(path);
			path = NULL;
		}
	}
	return (path);
}

static char	*get_complete_path(
	const char *suffix,
	char **path_array
	)
{
	char	*path;
	size_t	i;

	path = NULL;
	i = 0;
	while (path_array[i] != NULL)
	{
		path = ft_strjoin(path_array[i], suffix);
		if (path == NULL)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (path != NULL)
		clean_path(&path);
	return (path);
}

static char	**get_split_path(char **env, const char *pathvar_name)
{
	char	*joint_path;
	char	**path_array;
	size_t	i;

	i = 0;
	while (env[i] != NULL && is_path_var(env[i], pathvar_name) == false)
		i++;
	joint_path = replace_str(env[i], EMPTY_STR, 0, ft_strlen(pathvar_name) + 1);
	path_array = ft_split(joint_path, COLON);
	if (path_array != NULL)
		add_fwd_slash(path_array);
	free(joint_path);
	return (path_array);
}

char	*get_path_from_env(
	const char *suffix,
	const char *pathvar_name,
	char **env
	)
{
	char	**path_array;
	char	*path;

	if (is_var_path_in_env(env, pathvar_name) == false
		|| is_empty_str(suffix) == true)
		return (NULL);
	path_array = get_split_path(env, pathvar_name);
	if (path_array == NULL)
		return (NULL);
	path = get_complete_path(suffix, path_array);
	free_strs(path_array);
	return (path);
}
