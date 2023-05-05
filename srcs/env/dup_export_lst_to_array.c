/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_export_lst_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:02 by mat               #+#    #+#             */
/*   Updated: 2023/05/04 16:13:58 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_assign_from_var(t_var *var)
{
	char	*tmp;
	char	*tmp2;
	char	*assign;

	tmp = NULL;
	if (var->value != NULL)
	{
		tmp = ft_strjoin("\"", var->value);
		tmp2 = ft_strjoin_free(tmp, "\"");
		tmp = ft_strjoin(EQUAL_SIGN_STR, tmp2);
		free(tmp2);
	}
	assign = ft_strjoin(var->key, tmp);
	free(tmp);
	return (assign);
}

static size_t	get_export_array_size(t_list *env)
{
	size_t	size;
	t_var	*var_tmp;

	size = 0;
	while (env != NULL)
	{
		var_tmp = env->content;
		if (var_tmp->flags & EXPORT_MASK)
			size++;
		env = env->next;
	}
	return (size);
}

static void	cpy_export_lst_to_array(char **array, t_list *env)
{
	t_var	*var_tmp;

	while (env != NULL)
	{
		var_tmp = env->content;
		if (var_tmp->flags & EXPORT_MASK)
			*array = get_assign_from_var(env->content);
		env = env->next;
		++array;
	}
	*array = NULL;
}

char	**dup_export_lst_to_array(t_list *env_lst)
{
	const size_t	size = get_export_array_size(env_lst);
	char			**env_array;

	env_array = (char **)malloc((size + 1) * sizeof(char *));
	if (env_array != NULL)
		cpy_export_lst_to_array(env_array, env_lst);
	return (env_array);
}
