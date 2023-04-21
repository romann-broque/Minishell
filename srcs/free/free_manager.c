/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:28:17 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 11:10:49 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	free_command_lst(void *ptr)
{
	ft_lstclear((t_list **)&ptr, (void (*)(void *))free_command);
}

void	free_token_lst(void *ptr)
{
	ft_lstclear((t_list **)&ptr, (void (*)(void *))free_token);
}

static void	run_deallocator(t_deallocator *dealloc)
{
	dealloc->free_fct(dealloc->ptr);
}

void	free_manager(void)
{
	const size_t	deallocator_count = g_global.tracker.index;
	size_t			i;

	i = 0;
	while (i < deallocator_count)
	{
		run_deallocator(g_global.tracker.deallocator_array + i);
		++i;
	}
	init_tracker();
}
