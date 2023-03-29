/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:52:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/28 19:23:54 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(char **const token_array)
{
	if (token_array[0] != NULL && streq(token_array[0], "exit"))
		exit_shell(LAST_RETVAL);
}

static void	get_command(void)
{
	char *const		line = readline(PROMPT);
	char *const		line_w_var = expand_var(line);
	char **const	token_array = ft_split_set(line_w_var, SEPARATORS);

	if (token_array == NULL)
		exit_shell(LAST_RETVAL);
	else
		exec_command(token_array);
	print_command(token_array);
	free_strs(token_array);
}

void	prompt(void)
{
	set_catcher();
	while (true)
		get_command();
}
