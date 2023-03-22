/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/22 12:41:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_command(void)
{
	char *const	command = readline(PROMPT);

	if (streq(command, "exit"))
		exit_shell(EXIT_SUCCESS);
	if (command == NULL)
		exit_shell(EXIT_SUCCESS);
	free(command);
}

void	prompt(void)
{
	while (true)
		get_command();
}
