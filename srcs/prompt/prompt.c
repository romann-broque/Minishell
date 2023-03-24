/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/24 13:47:30 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(char **const command)
{
	if (streq(command[0], "exit"))
		exit_shell(LAST_RETVAL);
}

static void	get_command(void)
{
	char *const		line = readline(PROMPT);
	char **const	command = ft_split_set(line, SEPARATORS);

	free(line);
	if (command == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(command);
	print_command(command);
	free(command);
}

void	prompt(void)
{
	set_catcher();
	while (true)
		get_command();
}
