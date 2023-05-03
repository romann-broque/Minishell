/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env_lst_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:52:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 10:21:33 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_assign_from_var(t_var *var)
{
	char *const	assign = ft_strjoin(var->key, EQUAL_SIGN_STR);

	return (ft_strjoin_free(assign, var->value));
}

static void	cpy_env_lst_to_array(char **array, t_list *env, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		array[i] = get_assign_from_var(env->content);
		env = env->next;
		++i;
	}
	array[i] = NULL;
}

char	**dup_envs_lst_to_array(t_list *env_lst1, t_list *env_lst2)
{
	const size_t	size1 = ft_lstsize(env_lst1);
	const size_t	size2 = ft_lstsize(env_lst2);
	char			**env_array;

	env_array = (char **)malloc((size1 + size2 + 1) * sizeof(char *));
	if (env_array != NULL)
	{
		cpy_env_lst_to_array(env_array, env_lst1, size1);
		cpy_env_lst_to_array(env_array + size1, env_lst2, size2);
	}
	return (env_array);
}
