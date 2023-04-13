/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:28:17 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/13 14:38:50 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_resource_tracker	g_tracker;

void	free_command_lst(void *ptr)
{
	ft_lstclear((t_list **)ptr, (void (*)(void *))free_command);
}

void	free_token_lst(void *ptr)
{
	ft_lstclear((t_list **)ptr, (void (*)(void *))free_token);
}

static void	run_deallocator(t_deallocator *dealloc)
{
	dealloc->free_fct(dealloc->ptr);
}

void	free_manager(void)
{
	const size_t	deallocator_count = g_tracker.index;
	size_t			i;

	i = 0;
	while (i < deallocator_count)
	{
		run_deallocator(g_tracker.deallocator_array + i);
		++i;
	}
	g_tracker.index = 0;
}
