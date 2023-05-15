/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/05 16:13:38 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

t_var	*get_var_from_env(const char *key, t_list *env)
{
	t_var	*var;

	while (env != NULL)
	{
		var = env->content;
		if (streq(var->key, key) == true)
			return (var);
		env = env->next;
	}
	return (NULL);
}

void	change_var(
	const char *key,
	const char *value,
	uint8_t flags,
	t_list **env
	)
{
	t_var *const	var = get_var_from_env(key, *env);

	if (value != NULL)
		flags |= SET_MASK;
	if (var == NULL)
		ft_lstadd_back(env,
			ft_lstnew(init_var(key, value, flags)));
	else
	{
		if (value != NULL)
		{
			free(var->value);
			var->value = ft_strdup(value);
		}
		var->flags |= flags;
	}
}

void	update_var(const char *key, const char *value, const uint8_t flags)
{
	change_var(key, value, flags, &(g_global.env));
}
