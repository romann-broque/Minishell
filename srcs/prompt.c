/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/22 16:12:42 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_command(void)
{
	char *const	line = readline(PROMPT);
	char *const	command = ft_strtrim(line, SEPARATORS);

	free(line);
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
