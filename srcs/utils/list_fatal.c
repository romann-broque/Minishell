/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fatal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:28:45 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/26 22:55:21 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_fatal(void *ptr, void (*free_fct)(void *))
{
	t_list	*node;

	node = NULL;
	if (ptr != NULL)
	{
		node = ft_lstnew(ptr);
		add_deallocator(ptr, free_fct);
		add_deallocator(node, free);
	}
	if (ptr == NULL || node == NULL)
		exit_alloc();
	return (node);
}

void	ft_lstaddback_fatal(
			t_list **lst,
			void *ptr,
			void (*free_fct)(void *)
			)
{
	ft_lstadd_back(lst, ft_lstnew_fatal(ptr, free_fct));
}

void	ft_lstaddfront_fatal(
			t_list **lst,
			void *ptr,
			void (*free_fct)(void *)
			)
{
	ft_lstadd_front(lst, ft_lstnew_fatal(ptr, free_fct));
}
