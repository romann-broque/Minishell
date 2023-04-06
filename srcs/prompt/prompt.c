/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 10:06:34 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_list	const *token_lst)
{
	t_token *const	token = token_lst->content;

	if (token != NULL
		&& (token->value != NULL)
		&& streq(token->value, "exit"))
		exit_shell(LAST_RETVAL);
}

static void	handle_command(const char *command)
{
	t_list	*tokens;

	tokens = lexer_root(command);
	if (tokens == NULL)
		exit_shell(LAST_RETVAL);
	else
	{
		expand_command(tokens);
		exec_command(tokens);
	}
	print_command(tokens);
	ft_lstclear(&tokens, (void (*)(void *))free_token);
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
