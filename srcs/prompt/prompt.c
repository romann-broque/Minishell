/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/12 14:11:21 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_list *token_lst, const char **env)
{
	t_token *const	token = token_lst->next->content;
	t_list			*cmds;

	if (token != NULL
		&& (token->value != NULL)
		&& streq(token->value, "exit"))
	{
		ft_lstclear(&token_lst, (void (*)(void *))free_token);
		exit_shell(LAST_RETVAL);
	}
	else
	{
		cmds = interpreter(token_lst, env);
		ft_lstclear(&cmds, (void (*)(void *))free_command);
	}
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
			exec_command(tokens, env);
		}
		else
			print_error(PARS_ERROR);
	}
	print_command(tokens);
	ft_lstclear(&tokens, (void (*)(void *))free_token);
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
		get_command(env);
}
