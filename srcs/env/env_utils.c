/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:01:41 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 18:39:30 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

t_var	*init_var(const char *name, const char *value, const uint8_t flags)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (new != NULL)
	{
		new->key = ft_strdup(name);
		new->value = ft_strdup(value);
		new->flags = flags;
	}
	return (new);
}

t_var	*dup_var(t_var *var)
{
	return (init_var(var->key, var->value, var->flags));
}

t_var	*get_var(const char *var_name)
{
	t_list	*env;
	t_var	*var;

	env = g_global.env;
	while (env != NULL)
	{
		var = env->content;
		if (streq(var->key, var_name) == true)
			return (var);
		env = env->next;
	}
	return (NULL);
}

void	set_var_flag(const char *key, const uint8_t flags)
{
	t_var *const	var = get_var(key);

	if (var != NULL)
		var->flags = flags;
}

void	free_var(t_var *var)
{
	if (var != NULL)
	{
		free(var->key);
		free(var->value);
	}
	free(var);
}
