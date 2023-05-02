/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env_lst_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:52:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/02 15:03:44 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_assign_from_var(t_var *var)
{
	char *const	assign = ft_strjoin(var->name, EQUAL_SIGN_STR);

	return (ft_strjoin_free(assign, var->value));
}

static void	cpy_env_lst_to_array(char **array, t_list *env)
{
	while (env != NULL)
	{
		*array = get_assign_from_var(env->content);
		env = env->next;
		++array;
	}
	*array = NULL;
}

char	**dup_env_lst_to_array(t_list *env_lst)
{
	const size_t	size = ft_lstsize(env_lst);
	char			**env_array;

	env_array = (char **)malloc((size + 1) * sizeof(char *));
	if (env_array != NULL)
		cpy_env_lst_to_array(env_array, env_lst);
	return (env_array);
}
