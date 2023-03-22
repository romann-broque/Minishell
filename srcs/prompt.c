/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/22 11:23:32 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_command(void)
{
	char *const	command = get_next_line(STDIN_FILENO);
	const char	eof[] = {EOF, '\0'};
	printf("\n[%s]\n", command);
	printf("\n[%s]\n", eof);
	if (command == NULL)
		exit(EXIT_SUCCESS);
	free(command);
	return (command != NULL);
}

void	prompt(void)
{
	while (true)
	{
		ft_printf("%s", PROMPT);
		while (get_command() == false)
			;
	}
}
