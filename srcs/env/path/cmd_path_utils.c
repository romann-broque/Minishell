/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:58:46 by mat               #+#    #+#             */
/*   Updated: 2023/05/29 13:57:23 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_path_from_cmd(t_command *cmd)
{
	char *const	path = ft_strdup(cmd->command[0]);

	if (path != NULL)
		return (path);
	return (NULL);
}

bool	is_var_path_in_env(char **env, const char *pathvar_name)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL && is_path_var(env[i], pathvar_name) == false)
		i++;
	return (env[i] != NULL);
}

bool	is_empty_str(const char *str)
{
	return (streq(EMPTY_STR, str));
}

bool	is_path_var(const char *env_line, const char *pathvar_name)
{
	const size_t	eq_offset = abs_index(env_line, EQUAL_SIGN);

	return (ft_strncmp(pathvar_name, env_line, eq_offset) == 0);
}

void	add_fwd_slash(char **path_array)
{
	char	*str_tmp;
	size_t	i;

	i = 0;
	while (path_array[i] != NULL)
	{
		str_tmp = path_array[i];
		path_array[i] = ft_strjoin(path_array[i], FWD_SLASH_STR);
		free(str_tmp);
		i++;
	}
}
