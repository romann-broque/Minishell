/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/28 13:37:07 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(char **const token_array)
{
	if (token_array[0] != NULL && streq(token_array[0], "exit"))
		exit_shell(LAST_RETVAL);
}

static void	get_command(void)
{
	char *const		line = readline(PROMPT);
	char **const	token_array = get_tokens(line);

	free(line);
	if (token_array == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(token_array);
	free_strs(token_array);
}

void	prompt(void)
{
	set_catcher();
	while (true)
		get_command();
}
