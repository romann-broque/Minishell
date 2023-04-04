/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 15:33:24 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(char **const token_array)
{
	if (token_array[0] != NULL && streq(token_array[0], "exit"))
		exit_shell(LAST_RETVAL);
}

static void	handle_command(const char *command)
{
	char *const		line_w_var = expand_var(command);
	char **const	token_array = get_tokens(line_w_var);

	free(line_w_var);
	if (token_array == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(token_array);
	print_command(token_array);
	free_strs(token_array);
}

static void	get_command(void)
{
	char *const	line = readline(PROMPT);

	if (are_quotes_closed(line) == true)
		handle_command(line);
	else
		print_error(SYNTAX_ERROR);
	free(line);
}

void	prompt(void)
{
	set_catcher();
	while (true)
		get_command();
}
