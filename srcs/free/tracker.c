/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:27:19 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/17 18:55:16 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static t_deallocator	*init_dealloc(void *ptr, void (*fct)(void *))
{
	t_deallocator	*dealloc;

	dealloc = (t_deallocator *)malloc(sizeof(t_deallocator));
	if (dealloc != NULL)
	{
		dealloc->ptr = ptr;
		dealloc->free_fct = fct;
	}
	return (dealloc);
}

void	add_deallocator(void *ptr, void (*fct)(void *))
{
	t_deallocator *const	dealloc = init_dealloc(ptr, fct);

	ft_lstadd_front(&(g_global.garbage), ft_lstnew(dealloc));
}

bool	are_same_ptr(void *ptr1, void *ptr2)
{
	return (ptr1 == ptr2);
}

void	rm_deallocator(void *ptr)
{
	ft_list_remove_if(&(g_global.garbage), ptr, are_same_ptr, free);
}

void	init_tracker(void)
{
	g_global.garbage = NULL;
}
