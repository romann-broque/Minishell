/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:27:19 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 11:11:10 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	add_deallocator(void *ptr, void (*fct)(void *))
{
	t_deallocator *const		curr_deallocator
		= g_global.tracker.deallocator_array + g_global.tracker.index;

	curr_deallocator->ptr = ptr;
	curr_deallocator->free_fct = fct;
	++(g_global.tracker.index);
}

void	init_tracker(void)
{
	t_deallocator *const		curr_dealloc
		= g_global.tracker.deallocator_array;
	size_t						i;

	i = 0;
	while (i < NB_DEALLOCATOR)
	{
		curr_dealloc[i].ptr = NULL;
		curr_dealloc[i].free_fct = NULL;
		++i;
	}
	g_global.tracker.index = 0;
}
