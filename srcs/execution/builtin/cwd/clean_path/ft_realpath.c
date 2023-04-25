/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:51:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/25 17:03:39 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_realpath(const char *path, char *resolved, char *left)
{
	if (path[0] == FWD_SLASH)
	{
		ft_strcpy(resolved, FWD_SLASH_STR);
		if (path[1] != '\0')
			ft_strlcpy(left, path + 1, PATH_MAX);
	}
}

static void	silent_trailing_slash(char *str, const size_t len)
{
	if (len > 1 && str[len - 1] == FWD_SLASH)
		str[len - 1] = '\0';
}

char	*ft_realpath(const char *path, char resolved[PATH_MAX])
{
	size_t	left_len;
	size_t	resolved_len;
	char	left[PATH_MAX];

	init_realpath(path, resolved, left);
	left_len = ft_strlen(left);
	resolved_len = ft_strlen(resolved);
	if (left_len >= sizeof(left) || resolved_len >= PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return (NULL);
	}
	if (clean_path_comp(left, &left_len, resolved, &resolved_len) == NULL)
		return (NULL);
	silent_trailing_slash(resolved, resolved_len);
	return (resolved);
}
