/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:27:19 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/26 15:46:55 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_same_deallocator(t_deallocator deal1, t_deallocator deal2)
{
	return (deal1.ptr == deal2.ptr);
}

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

void	rm_deallocator(void *ptr)
{
	t_deallocator *const	ref = init_dealloc(ptr, NULL);

	ft_list_remove_if(&(g_global.garbage),
		(void *)&ref,
		(bool (*)(void *, void *))is_same_deallocator,
		free);
	free(ref);
}

void	add_deallocator(void *ptr, void (*fct)(void *))
{
	t_deallocator *const	dealloc = init_dealloc(ptr, fct);
	t_list *const			new_deal = ft_lstnew(dealloc);

	if (new_deal == NULL || dealloc == NULL)
	{
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
