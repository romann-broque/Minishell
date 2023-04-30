/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/30 22:14:04 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	exec_command(t_list **token_lst)
{
	t_list	*cmds;

	cmds = interpreter(*token_lst, g_global.env);
	add_deallocator(cmds, free_command_lst);
	ft_lstiter(cmds, (void (*)(void *))execution);
}

static void	handle_command(const char *command)
{
	t_list	*tokens;

	tokens = lexer(command);
	if (tokens == NULL)
		exit_shell(LAST_RETVAL, true);
	else
	{
		add_deallocator(tokens, free_token_lst);
		if (parser(tokens) == true)
		{
			expand_command(&tokens);
			exec_command(&tokens);
		}
	}
}

static void	get_command(void)
{
	char *const	line = readline(PROMPT);

	add_history(line);
	add_deallocator(line, free);
	if (are_quotes_closed(line) == true)
		handle_command(line);
	else
		print_error("%s: %s\n", MINISHELL, SYNTAX_ERROR);
	free_manager();
}

void	prompt(void)
{
	while (true)
		get_command();
}
