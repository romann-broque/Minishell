/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:35:37 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/13 14:36:30 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(const int exit_value)
{
	ft_dprintf(STDERR_FILENO, "%s\n", EXIT_MESSAGE);
	exit(exit_value);
}

void	exit_builtin(void)
{
	free_manager();
	exit_shell(LAST_RETVAL);
}
