/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:58:46 by mat               #+#    #+#             */
/*   Updated: 2023/04/14 11:43:57 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_path_in_env(const char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL && is_path_var(env[i]) == false)
		i++;
	return (env[i] != NULL);
}

bool	is_empty_cmd(t_command *cmd)
{
	return (streq(EMPTY_STR, cmd->command[0]));
}

bool	is_path_var(const char *env_line)
{
	return (ft_strncmp(PATH_VAR, env_line, PATH_VAR_LEN) == 0);
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
