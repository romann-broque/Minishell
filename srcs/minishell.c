/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:07:50 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 00:30:04 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_size_strs(char **strs)
{
	size_t	size;

	size = 0;
	while (strs[size] != NULL)
		++size;
	return (size);
}

static void	cpy_strs(char **dest, char **src)
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

int	main(
	__attribute__((unused)) int ac,
	__attribute__((unused)) char **av,
	char **env)
{
	env = dup_strs(env);
	add_deallocator(env, (void (*)(void *))free_strs);
	prompt(env);
	return (EXIT_SUCCESS);
}
