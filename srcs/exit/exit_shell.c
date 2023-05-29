/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:35:37 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 18:01:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	*g_global;

static void	close_fds(void)
{
	close_safe(g_global->stdin);
	close_safe(g_global->stdout);
	close_safe(g_global->hd_pipe[0]);
	close_safe(g_global->hd_pipe[1]);
}

static void	free_global(void)
{
	free_manager();
	ft_lstclear(&(g_global->env), (void (*)(void *))free_var);
	close_fds();
	free(g_global);
}

void	exit_shell(const int exit_value, const bool is_print)
{
	if (is_print == true && isatty(STDIN_FILENO) == 1)
		ft_dprintf(STDERR_FILENO, "%s\n", EXIT_MESSAGE);
	free_global();
	exit(exit_value);
}
