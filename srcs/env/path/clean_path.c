/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:41:38 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/22 18:41:55 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_cleanpath_size(char *path)
{
	size_t	i;
	size_t	count;
	bool	is_slash;

	count = 0;
	i = 0;
	is_slash = false;
	while (path[i] != '\0')
	{
		if (path[i] == FWD_SLASH)
		{
			count += (is_slash == true);
			is_slash = true;
		}
		else
			is_slash = false;
		++i;
	}
	return (ft_strlen(path) - count);
}

static void	cpy_cleanpath(char *dest, char *src, const size_t new_len)
{
	size_t	i;
	size_t	index;
	bool	is_slash;

	i = 0;
	index = 0;
	is_slash = false;
	while (index < new_len)
	{
		if (src[index + i] != FWD_SLASH || is_slash == false)
		{
			dest[index] = src[index + i];
			is_slash = (src[index + i] == FWD_SLASH);
			++index;
		}
		else
		{
			is_slash = true;
			++i;
		}
	}
	dest[new_len] = '\0';
}

void	clean_path(char **path)
{
	const size_t	new_len = get_cleanpath_size(*path);
	char			*new;

	new = (char *)malloc((new_len + 1) * sizeof(char));
	if (new != NULL)
		cpy_cleanpath(new, *path, new_len);
	free(*path);
	*path = new;
}
