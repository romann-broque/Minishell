/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/21 16:42:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_command(void)
{
	char *const	command = get_next_line(STDIN_FILENO);

	free(command);
	return (command != NULL);
}

/*
** then, execute the command
*/

void	prompt(void)
{
	while (true)
	{
		ft_printf("%s", PROMPT);
		while (get_command() == false)
			;
	}
}
