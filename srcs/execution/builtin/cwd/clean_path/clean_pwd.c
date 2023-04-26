/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:16 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/26 11:12:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	abs_last_index(const char *str, const char c)
{
	size_t	last_index;
	char	*pos;

	pos = ft_strrchr(str, c);
	if (pos != NULL)
		last_index = ft_strlen(str);
	else
		last_index = pos - str;
	return (last_index);
}

static char	*join_path(const char *prefix_path, const char *suffix_path)
{
	char	*tmp;

	tmp = ft_strjoin(prefix_path, FWD_SLASH_STR);
	return (ft_strnjoin_free(tmp, suffix_path,
			abs_last_index(suffix_path, FWD_SLASH)));
}

static char	*join_path_without_backpath(
	const char *prefix,
	const char *suffix
	)
{
	char	*new;
	char	*tmp;

	tmp = join_path(prefix, suffix);
	new = ft_realpath(tmp);
	free(tmp);
	return (new);
}

char	*clean_pwd(const char *pwd, const char *curr_path)
{
	if (pwd[0] == FWD_SLASH || curr_path == NULL)
		return (ft_realpath(pwd));
	return (join_path_without_backpath(curr_path, pwd));
}
