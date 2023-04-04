/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 10:45:39 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_list	const *token_lst)
{
	if (token_lst->content != NULL && streq(token_lst->content, "exit"))
		exit_shell(LAST_RETVAL);
}

static void	handle_command(const char *command)
{
	t_list	*token_lst;

	token_lst = get_tokens(command);
	if (token_lst == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(token_lst);
	print_command(token_lst);
	ft_lstclear(&token_lst, free);
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
