/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:31:24 by mat               #+#    #+#             */
/*   Updated: 2023/05/14 10:53:14 by rbroque          ###   ########.fr       */
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
	if (g_global.is_stoppable == true)
	{
		g_global.is_stoppable = false;
		g_global.child_pid = 0;
	}
}
