/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_from_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:22:38 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/28 22:23:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_strs_from_lst(char **dest_strs, t_list *lst, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dest_strs[i] = ft_strdup((char *)(lst->content));
		if (dest_strs[i] == NULL)
		{
			free_strs(dest_strs);
			break ;
		}
		lst = lst->next;
		++i;
	}
	dest_strs[size] = NULL;
}

char	**dup_strs_from_lst(t_list *lst)
{
	const size_t	size = ft_lstsize(lst);
	char			**strs;

	strs = (char **)malloc((size + 1) * sizeof(char *));
	if (strs != NULL)
		cpy_strs_from_lst(strs, lst, size);
	return (strs);
}
