/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 15:25:23 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_list *token_lst)
{
	t_token *const	token = token_lst->next->content;

	if (token != NULL
		&& (token->value != NULL)
		&& streq(token->value, "exit"))
	{
		ft_lstclear(&token_lst, (void (*)(void *))free_token);
		exit_shell(LAST_RETVAL);
	}
}

static void	handle_command(const char *command)
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
			exec_command(tokens);
		}
		else
			print_error(PARS_ERROR);
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
