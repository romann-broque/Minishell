/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:27:19 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/13 15:13:05 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_resource_tracker	g_tracker;

void	add_deallocator(void *ptr, void (*fct)(void *))
{
	t_deallocator *const	curr_deallocator
		= g_tracker.deallocator_array + g_tracker.index;

	curr_deallocator->ptr = ptr;
	curr_deallocator->free_fct = fct;
	++(g_tracker.index);
}

void	init_tracker(void)
{
	t_deallocator *const	curr_dealloc = g_tracker.deallocator_array;
	size_t					i;

	i = 0;
	while (i < NB_DEALLOCATOR)
	{
		curr_dealloc[i].ptr = NULL;
		curr_dealloc[i].free_fct = NULL;
		++i;
	}
	g_tracker.index = 0;
}
