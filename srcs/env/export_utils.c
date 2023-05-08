/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:30:43 by mat               #+#    #+#             */
/*   Updated: 2023/05/07 16:08:48 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*get_value_from_assign(
	char *str,
	const bool is_assign,
	const size_t eq_index
	)
{
	char	*value;

	value = NULL;
	if (is_assign == true)
		value = str + eq_index + 1;
	return (value);
}

t_var	*export_var_from_str(char *str, const bool is_assign)
{
	const size_t	eq_index = abs_index(str, EQUAL_SIGN);
	char *const		name = ft_strndup(str, eq_index);
	const char		*value = get_value_from_assign(str, is_assign, eq_index);
	t_var			*new_var;

	new_var = init_var(name, value, EXPORT_MASK);
	free(name);
	return (new_var);
}

void	sort_strings(char *strings[])
{
	size_t		i;
	size_t		j;

	i = 0;
	while (strings[i] != NULL)
	{
		j = i;
		while (strings[j] != NULL)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
				ft_swap((void **)&strings[i], (void **)&strings[j]);
			j++;
		}
		i++;
	}
}
