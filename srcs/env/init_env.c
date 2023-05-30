/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:30:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/28 12:43:24 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*init_var_from_str(const char *str)
{
	const size_t	eq_index = abs_index(str, EQUAL_SIGN);
	char *const		name = ft_strndup(str, eq_index);
	const char		*value = str + eq_index + 1;
	t_var			*new_var;

	if (name == NULL)
		exit_alloc();
	new_var = init_var(name, value, ENV_MASK);
	free(name);
	return (new_var);
}

static t_list	*get_env_from_strs(char **env_strs)
{
	t_list	*env_lst;
	t_list	*new_node;
	t_var	*new_var;

	env_lst = NULL;
	while (*env_strs != NULL)
	{
		new_var = init_var_from_str(*env_strs);
		if (new_var == NULL)
			exit_alloc();
		new_node = ft_lstnew(new_var);
		if (new_node == NULL)
		{
			free_var(new_var);
			exit_alloc();
		}
		ft_lstadd_back(&env_lst, new_node);
		++env_strs;
	}
	return (env_lst);
}

void	init_env(t_global *global, char **env)
{
	global->env = get_env_from_strs(env);
	if (*env != NULL && global->env == NULL)
	{
		perror(MALLOC_ERROR);
		exit(EXIT_FAILURE);
	}
}
