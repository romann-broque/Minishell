/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/25 18:42:50 by rbroque          ###   ########.fr       */
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
		ft_lstaddback_fatal(env,
			init_var(key, value, flags), (void (*)(void *))free_var);
	else
	{
		if (value != NULL)
		{
			free(var->value);
			var->value = ft_strdup(value);
			if (var->value == NULL)
				exit_alloc();
		}
		var->flags |= flags;
	}
}

void	update_var(const char *key, const char *value, const uint8_t flags)
{
	change_var(key, value, flags, &(g_global.env));
}
