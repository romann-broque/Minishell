/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:35:37 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/02 10:52:02 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	exit_shell(const int exit_value, const bool is_print)
{
	if (is_print == true)
		ft_dprintf(STDERR_FILENO, "%s\n", EXIT_MESSAGE);
	free_manager();
	free_strs(g_global.env);
	exit(exit_value);
}
