/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:58:46 by mat               #+#    #+#             */
/*   Updated: 2023/04/13 14:51:49 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_path_in_env(const char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	return (env[i] != NULL);
}

bool	is_empty_cmd(t_command *cmd)
{
	return (streq(EMPTY_STR, cmd->command[0]));
}

void	add_fwd_slash(char ***paths)
{
	char	*str_tmp;
	size_t	i;

	i = 0;
	while ((*paths)[i] != NULL)
	{
		str_tmp = (*paths)[i];
		(*paths)[i] = ft_strjoin((*paths)[i], "/");
		free(str_tmp);
		i++;
	}
}
