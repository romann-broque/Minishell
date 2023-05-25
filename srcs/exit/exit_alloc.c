/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/25 14:27:45 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	exit_alloc(void)
{
	print_error("%s: ", MINISHELL);
	perror(MALLOC_ERROR);
	exit_shell(g_global.last_ret_val, false);
}
