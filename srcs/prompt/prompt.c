/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/22 10:12:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	exec_command(t_list **token_lst)
{
	t_list	*cmds;

	cmds = interpreter(*token_lst, g_global.env);
	ft_lstiter(cmds, (void (*)(void *))execution);
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

static void	add_line_to_history(const char *line)
{
	if (line != NULL && *line != '\0')
		add_history(line);
}

static void	get_command(void)
{
	char *const	line = readline(PROMPT);

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
}

void	prompt(void)
{
	while (true)
		get_command();
}
