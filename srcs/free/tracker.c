/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:27:19 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/28 13:04:38 by rbroque          ###   ########.fr       */
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
	t_list *const			new_deal = ft_lstnew(dealloc);

	if (new_deal == NULL || dealloc == NULL)
	{
		if (fct != NULL)
			fct(ptr);
		free(dealloc);
		free(new_deal);
		exit_alloc();
	}
	ft_lstadd_front(&(g_global.garbage), new_deal);
}

void	init_tracker(void)
{
	g_global.garbage = NULL;
}
