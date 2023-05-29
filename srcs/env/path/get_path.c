/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:59 by mat               #+#    #+#             */
/*   Updated: 2023/05/29 14:01:11 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		|| is_empty_str(suffix) == true
		|| suffix[0] == DOT)
		return (NULL);
	path_array = get_split_path(env, pathvar_name);
	if (path_array == NULL)
		return (NULL);
	path = get_complete_path(suffix, path_array);
	free_strs(path_array);
	return (path);
}
