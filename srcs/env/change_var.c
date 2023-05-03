/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 14:51:01 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	change_var(const char *key, const char *value, uint8_t flags)
{
	t_var *const	var = get_var(key);

	if (value != NULL)
		flags &= SET_MASK;
	if (var == NULL)
		ft_lstadd_back(&(g_global.env),
			ft_lstnew(init_var(key, value, flags)));
	else
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
}

void	update_var(const char *key, const char *value)
{
	change_var(key, value, ENV_MASK);
}
