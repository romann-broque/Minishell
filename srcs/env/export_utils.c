/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:30:43 by mat               #+#    #+#             */
/*   Updated: 2023/05/06 18:41:36 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

t_var	*export_var_from_str(char *str, bool is_assign)
{
	const size_t	eq_index = abs_index(str, EQUAL_SIGN);
	char *const		name = ft_strndup(str, eq_index);
	char			*value;
	t_var			*new_var;

	value = NULL;
	if (is_assign == true)
	{
		value = str + eq_index + 1;
		new_var = init_var(name, value, ENV_MASK);
	}
	else
		new_var = init_var(name, value, EXPORT_MASK);
	free(name);
	return (new_var);
}

void	sort_strings(char *strings[])
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (strings[i] != NULL)
	{
		j = 0;
		while (strings[j] != NULL)
		{
			if (ft_strcmp(strings[i], strings[j]) < 0)
			{
				tmp = strings[i];
				strings[i] = strings[j];
				strings[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
