/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/13 15:24:47 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_resource_tracker	g_tracker;

static void	exec_command(t_list **token_lst, const char **env)
{
	t_list	*cmds;

	cmds = interpreter(*token_lst, env);
	add_deallocator(&cmds, free_command_lst);
	add_deallocator(token_lst, free_token_lst);
	ft_lstiter(cmds, (void (*)(void *))execution);
	ft_lstclear(&cmds, (void (*)(void *))free_command);
}

static void	handle_command(const char *command, const char **env)
{
	t_list	*tokens;

	tokens = lexer(command);
	if (tokens == NULL)
		exit_shell(LAST_RETVAL);
	else
	{
		if (parser(tokens) == true)
		{
			expand_command(tokens);
			exec_command(&tokens, env);
			print_command(tokens);
			ft_lstclear(&tokens, (void (*)(void *))free_token);
		}
		else
			print_error(PARS_ERROR);
	}
}

static void	get_command(const char **env)
{
	char *const	line = readline(PROMPT);

	if (are_quotes_closed(line) == true)
		handle_command(line, env);
	else
		print_error(SYNTAX_ERROR);
	free(line);
}

void	prompt(const char **env)
{
	set_catcher();
	while (true)
	{
		init_tracker();
		get_command(env);
	}
}
