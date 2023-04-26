/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/26 15:19:34 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	exec_command(t_list **token_lst, char **env)
{
	t_list	*cmds;

	cmds = interpreter(*token_lst, env);
	add_deallocator(cmds, free_command_lst);
	g_global.is_stoppable = true;
	ft_lstiter(cmds, (void (*)(void *))execution);
}

static void	handle_command(const char *command, char **env)
{
	t_list	*tokens;

	tokens = lexer(command);
	if (tokens == NULL)
		exit_shell(LAST_RETVAL);
	else
	{
		add_deallocator(tokens, free_token_lst);
		if (parser(tokens) == true)
		{
			expand_command(&tokens);
			exec_command(&tokens, env);
		}
		else
			print_error(PARS_ERROR);
	}
}

static void	get_command(char **env)
{
	char *const	line = readline(PROMPT);

	g_global.is_stoppable = false;
	add_deallocator(line, free);
	if (are_quotes_closed(line) == true)
		handle_command(line, env);
	else
		print_error(SYNTAX_ERROR);
	free_manager();
}

void	prompt(char **env)
{
	init_global();
	set_catcher();
	while (true)
		get_command(env);
}
