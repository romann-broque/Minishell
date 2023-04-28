/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/28 15:34:52 by mdorr            ###   ########.fr       */
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
		exit_shell();
	else
	{
		add_deallocator(tokens, free_token_lst);
		if (parser(tokens) == true)
		{
			expand_command(&tokens);
			exec_command(&tokens);
		}
		else
			update_error_val(2);
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
	{
		update_error_val(2);
		print_error("%s: %s\n", MINISHELL, SYNTAX_ERROR);
	}
	free_manager();
}

void	prompt(void)
{
	while (true)
		get_command();
}
