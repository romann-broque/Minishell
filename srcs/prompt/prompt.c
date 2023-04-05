/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/05 01:01:47 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_list	const *token_lst)
{
	if (token_lst->content != NULL
		&& ((t_token *)(token_lst->content))->value != NULL
		&& streq(((t_token *)(token_lst->content))->value, "exit"))
		exit_shell(LAST_RETVAL);
}

static void	handle_command(const char *command)
{
	t_list	*tokens;

	tokens = get_token_lst(command);
	if (tokens == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(tokens);
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
