/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/02 16:14:00 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	change_var(const char *var_name, const char *var_value)
{
	t_var *const	var = get_var(var_name);

	if (var_value != NULL)
	{
		if (var == NULL)
			ft_lstadd_back(&(g_global.env),
				ft_lstnew(init_var(var_name, var_value, ENV_MASK)));
		else
		{
			free(var->value);
			var->value = ft_strdup(var_value);
		}
	}
}

// change name of change_var function