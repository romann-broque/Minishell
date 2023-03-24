/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/24 14:23:06 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(const char *command)
{
	if (streq(command, "exit"))
		exit_shell(LAST_RETVAL);
}

static void	get_command(void)
{
	char *const	line = readline(PROMPT);
	char *const	command = ft_strtrim(line, SEPARATORS);

	free(line);
	if (command == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(command);
	free(command);
}

void	prompt(void)
{
	set_catcher();
	while (true)
		get_command();
}
