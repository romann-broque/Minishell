/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:07 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 09:59:51 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_value(char **assign, const char *var_value)
{
	const size_t	len = ft_strlen(*assign);
	const size_t	offset = abs_index(*assign, '=');

	printf("before replace --> %s\n", *assign);
	*assign = replace_str_free(*assign, var_value, offset + 1, len - offset);
	printf("after replace --> %s\n", *assign);
}

void	change_var(char **env,
	const char *var_name, const char *var_value)
{
	const size_t	len = ft_strlen(var_name);
	size_t			i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var_name, len) != 0)
		++i;
	if (env[i] != NULL)
		change_value(env + i, var_value);
}
