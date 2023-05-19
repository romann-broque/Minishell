/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:32:39 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/19 15:17:23 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	clear_line_handler(__attribute__((unused)) int signal)
{
	clear_line();
}

void	handle_sigint_default(__attribute__((unused)) int signal)
{
	ft_printf(NEWLINE_STR);
	clear_line();
	g_global.last_ret_val = SIGINT_RETVAL;
}

void	handle_sigint_inter(__attribute__((unused))int signal)
{
	ft_printf(NEWLINE_STR);
	close(g_global.hd_pipe_in);
	close(g_global.hd_pipe_out);
	exit_shell(SIGINT_RETVAL, false);
}
