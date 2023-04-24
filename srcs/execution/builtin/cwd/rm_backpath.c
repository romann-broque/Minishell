/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_backpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:31:32 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/24 22:21:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_next_ptr(char **ptr)
{
	size_t	len;
	char	*tmp;
	char	*new_ptr;

	new_ptr = ft_strstr(*ptr, BACKPATH);
	if (new_ptr != NULL)
	{
		tmp = new_ptr;
		while (tmp > *ptr)
		{
			--tmp;
			if (*tmp == FWD_SLASH)
				break ;
		}
		len = new_ptr - tmp + BACKPATH_LEN;
		*ptr = new_ptr + BACKPATH_LEN;
		return (len);
	}
	return (0);
}

static size_t	get_clean_len(const char *path)
{
	char	*ptr;
	size_t	offset;
	size_t	len;

	len = ft_strlen(path);
	ptr = (char *)path;
	while (ptr != NULL && offset > 0)
	{
		offset = get_next_ptr(&ptr);
		len -= offset;
	}
	return (len);
}

static void	cpy_clean_path(char *dest, char *src, size_t final_len)
{
	size_t	i;
	size_t	offset;
	char	*ptr;

	ptr = src;
	i = 0;
	offset = SIZE_MAX;
	while (i < final_len && offset > 0)
	{
		offset = get_next_ptr(&ptr);
		if (offset == 0)
			ft_strcpy(dest + i, src);
		else
		{
			ft_strncpy(dest + i, src, ptr - src - offset);
			i += ptr - src - offset;
			src = ptr;
		}
	}
	dest[final_len] = '\0';
}

char	*rm_backpath(char *path)
{
	const size_t	len = get_clean_len(path);
	char			*clean;

	clean = (char *)malloc((len + 1) * sizeof(char));
	if (clean != NULL)
		cpy_clean_path(clean, path, len);
	printf("clean -> [%s]\n", clean);
	return (clean);
}
