/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:12:46 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/02 17:37:31 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv_local(const char *var_name, char **env)
{
	const size_t	var_len = ft_strlen(var_name);
	size_t			i;
	size_t			len;

	i = 0;
	while (env[i] != NULL)
	{
		len = abs_index(env[i], EQUAL_SIGN);
		if (len == var_len && ft_strncmp(env[i], var_name, len) == 0)
			return (env[i] + len + 1);
		++i;
	}
	return (NULL);
}

char	*ft_getenv(const char *var_name)
{
	t_var *const	var = get_var(var_name);

	if (var == NULL)
		return (NULL);
	return (var->value);
}
