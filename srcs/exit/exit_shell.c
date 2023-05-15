/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:35:37 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/15 20:44:06 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	exit_shell(const int exit_value, const bool is_print)
{
	if (is_print == true)
		ft_dprintf(STDERR_FILENO, "%s\n", EXIT_MESSAGE);
	free_manager();
	ft_lstclear(&(g_global.env), (void (*)(void *))free_var);
	close(g_global.pipes[0]);
	close(g_global.pipes[1]);
	exit(exit_value);
}
