/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env_lst_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:52:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/05 10:54:52 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_env_size(t_list *env, const uint8_t mask)
{
	t_var	*var;
	size_t	size;

	size = 0;
	while (env != NULL)
	{
		var = env->content;
		if (var->flags & mask)
			++size;
		env = env->next;
	}
	return (size);
}

static void	cpy_env_lst_to_array(
	char **array,
	t_list *env,
	const uint8_t mask,
	char *(*assign_fct)(t_var *)
	)
{
	t_var	*var;

	while (env != NULL)
	{
		var = env->content;
		if (var->flags & mask)
		{
			*array = assign_fct(var);
			++array;
		}
		env = env->next;
	}
	*array = NULL;
}

char	**dup_env_lst_to_array_gen(
	t_list *env_lst,
	const uint8_t mask,
	char *(*assign_fct)(t_var *)
	)
{
	const size_t	size = get_env_size(env_lst, mask);
	char			**env_array;

	env_array = (char **)malloc((size + 1) * sizeof(char *));
	if (env_array != NULL)
		cpy_env_lst_to_array(env_array, env_lst, mask, assign_fct);
	return (env_array);
}
