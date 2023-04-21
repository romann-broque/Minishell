/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:31:24 by mat               #+#    #+#             */
/*   Updated: 2023/04/21 13:33:25 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	init_global(void)
{
	init_tracker();
	g_global.is_stoppable = true;
	g_global.child_pid = 0;
}

void	update_global(void)
{
	g_global.is_stoppable = false;
	g_global.child_pid = 0;
}
