/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/20 16:17:31 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_correct_size(char **command)
{
	size_t	cmd_size;

	cmd_size = 0;
	while (command[cmd_size])
		cmd_size++;
	if (cmd_size > 2)
	{
		print_error("%s: %s: %s\n", MINISHELL, CD_BUILTIN, TOO_MANY_ARGS);
		return (false);
	}
	return (true);
}

static void	execute_cd(char *arg)
{
	if (arg == NULL)
		return ;
	else if (chdir(arg) == -1)
	{
		print_error("%s: %s: %s: ", MINISHELL, CD_BUILTIN, arg);
		perror(EMPTY_STR);
	}
}

void	cd_builtin(char **command)
{
	if (is_correct_size(command) == true)
		execute_cd(command[1]);
}
