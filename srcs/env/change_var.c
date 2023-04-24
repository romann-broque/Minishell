/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/24 22:03:22 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	change_value(char **assign, const char *var_value)
{
	const size_t	len = ft_strlen(*assign);
	const size_t	offset = abs_index(*assign, EQUAL_SIGN);

	*assign = replace_str_free(*assign, var_value, offset + 1, len - offset);
}

static void	add_str_in_strs(char ***strs, char *new)
{
	const size_t	size = get_size_strs(*strs);
	char			**new_strs;

	new_strs = (char **)malloc((size + 2) * sizeof(char *));
	if (new_strs != NULL)
	{
		cpy_strs(new_strs, *strs);
		new_strs[size] = new;
		new_strs[size + 1] = NULL;
	}
	*strs = new_strs;
}

static void	add_var(const char *var_name, const char *var_value)
{
	char	**tmp_strs;
	char	*tmp_str;
	char	*assign;

	if (var_name != NULL && var_value != NULL)
	{
		tmp_strs = g_global.env;
		assign = ft_strjoin(var_name, EQUAL_SIGN_STR);
		tmp_str = assign;
		assign = ft_strjoin(assign, var_value);
		add_str_in_strs(&(g_global.env), assign);
		free_strs(tmp_strs);
		free(tmp_str);
	}
}

void	change_var(const char *var_name, const char *var_value)
{
	const size_t	len = ft_strlen(var_name);
	size_t			offset;
	size_t			i;

	if (var_value != NULL)
	{
		i = 0;
		while (g_global.env[i] != NULL)
		{
			offset = abs_index(g_global.env[i], EQUAL_SIGN);
			if (offset == len
				&& ft_strncmp(g_global.env[i], var_name, offset) == 0)
				break ;
			++i;
		}
		if (g_global.env[i] != NULL)
			change_value(g_global.env + i, var_value);
		else
			add_var(var_name, var_value);
	}
}
