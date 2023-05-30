/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 17:49:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	*g_global;

static void	exec_command(t_list **token_lst)
{
	t_list	*cmds;

	cmds = interpreter(*token_lst, g_global->env);
	g_global->cmd_lst = cmds;
	if (g_global->is_stopped == false)
		ft_lstiter(cmds, (void (*)(void *))execution);
	close_pipe_fds();
	if (g_global->cmd_nbr > 1 && g_global->is_stopped == false)
		wait_for_exec();
	update_signal_state(S_DEFAULT);
}

static void	handle_command(const char *command)
{
	t_list	*tokens;

	tokens = lexer(command);
	if (tokens == NULL)
		exit_shell(g_global->last_ret_val, true);
	else
	{
		if (parser(tokens) == true)
		{
			expand_command(&tokens);
			exec_command(&tokens);
		}
		else
			update_error_val(INCORRECT_USE);
	}
}

static void	get_command(const t_reader line_reader)
{
	char *const	line = line_reader(PROMPT);

	update_signal_state(S_SLEEP);
	g_global->cmd_nbr = 0;
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
	g_global->is_stopped = false;
	update_signal_state(S_DEFAULT);
}

void	prompt(void)
{
	const int		is_interactive = isatty(STDIN_FILENO);
	const t_reader	line_reader = get_reader_fct(is_interactive);

	while (true)
		get_command(line_reader);
}
