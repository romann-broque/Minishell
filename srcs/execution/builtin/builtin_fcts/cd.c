/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:36:27 by mat               #+#    #+#             */
/*   Updated: 2023/04/19 11:16:50 by mat              ###   ########.fr       */
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
		print_error("cd : too many arguments\n");
		return (false);
	}
	return (true);
}

static void	execute_cd(char *arg)
{
	if (arg == NULL)
		return ;
	else if (chdir(arg) == -1)
		print_error("cd : wrong argument, inexistant path\n");
}

void	cd_builtin(char **command)
{
	if (is_correct_size(command) == true)
		execute_cd(command[1]);
}
