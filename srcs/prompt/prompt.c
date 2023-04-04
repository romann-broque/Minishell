/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 16:19:55 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_list	const *word_lst)
{
	if (word_lst->content != NULL && streq(word_lst->content, "exit"))
		exit_shell(LAST_RETVAL);
}

static void	handle_command(const char *command)
{
	t_list	*word_lst;

	word_lst = get_words(command);
	if (word_lst == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(word_lst);
	print_command(word_lst);
	ft_lstclear(&word_lst, free);
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
