/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/25 20:05:23 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	exec_command(t_list **token_lst)
{
	t_list	*cmds;

	cmds = interpreter(*token_lst, g_global.env);
	g_global.cmd_lst = cmds;
	ft_lstiter(cmds, (void (*)(void *))execution);
	close_pipe_fds();
	if (g_global.cmd_nbr > 1)
		wait_for_exec();
	update_signal_state(S_DEFAULT);
}

static void	handle_command(const char *command)
{
	t_list	*tokens;

	tokens = lexer(command);
	if (tokens == NULL)
		exit_shell(g_global.last_ret_val, true);
	else
	{
		add_deallocator(tokens, free_token_lst);
		if (parser(tokens) == true)
		{
			expand_command(&tokens);
			exec_command(&tokens);
		}
		else
			update_error_val(INCORRECT_USE);
	}
}

static void	get_command(void)
{
	char *const	line = readline(PROMPT);

	update_signal_state(S_SLEEP);
	g_global.cmd_nbr = 0;
	add_line_to_history(line);
	add_deallocator(line, free);
	if (are_quotes_closed(line) == true)
		handle_command(line);
	else
	{
		update_error_val(INCORRECT_USE);
		print_error("%s: %s\n", MINISHELL, SYNTAX_ERROR);
	}
	free_manager();
	update_signal_state(S_DEFAULT);
}

void	prompt(void)
{
	while (true)
		get_command();
}
