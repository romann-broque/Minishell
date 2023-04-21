/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:12:46 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 11:54:27 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*ft_getenv(char *var_name)
{
	char **const	env = g_global.env;
	size_t			i;
	size_t			len;

	i = 0;
	while (env[i] != NULL)
	{
		len = abs_index(env[i], EQUAL_SIGN);
		if (ft_strncmp(env[i], var_name, len) == 0)
			return (env[i] + len + 1);
		++i;
	}
	return (NULL);
}
// manage unexistant variables
