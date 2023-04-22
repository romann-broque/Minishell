/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:59 by mat               #+#    #+#             */
/*   Updated: 2023/04/22 18:51:14 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_path(t_command *cmd)
{
	return (is_in_str(cmd->command[0], FWD_SLASH));
}

char	*get_path_from_cmd(t_command *cmd)
{
	char *const	path = ft_strdup(cmd->command[0]);

	if (path != NULL && access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char	*get_path_cmd(const char *suffix, char **path_array)
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
		if (access(path, X_OK) == 0)
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
	path = get_path_cmd(suffix, path_array);
	free_strs(path_array);
	return (path);
}
