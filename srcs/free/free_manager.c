/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:28:17 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/30 22:04:06 by rbroque          ###   ########.fr       */
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
	if (dealloc->free_fct != NULL)
		dealloc->free_fct(dealloc->ptr);
}

void	free_manager(void)
{
	ft_lstiter(g_global.garbage, (void (*)(void *))run_deallocator);
	ft_lstclear(&(g_global.garbage), free);
	init_tracker();
}
