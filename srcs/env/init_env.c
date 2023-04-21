/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:30:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 15:24:35 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_size_strs(char **strs)
{
	size_t	size;

	size = 0;
	while (strs[size] != NULL)
		++size;
	return (size);
}

void	cpy_strs(char **dest, char **src)
{
	size_t	i;

	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
		{
			free_strs(dest);
			return ;
		}
		++i;
	}
	dest[i] = NULL;
}

static char	**dup_strs(char **strs)
{
	const size_t	size = get_size_strs(strs);
	char			**dup;

	dup = (char **)malloc((size + 1) * sizeof(char *));
	if (dup != NULL)
		cpy_strs(dup, strs);
	return (dup);
}

void	init_env(t_global *global, char **env)
{
	global->env = dup_strs(env);
	if (global->env == NULL)
	{
		perror(MALLOC_ERROR);
		exit(EXIT_FAILURE);
	}
}
