/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:16 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/25 17:12:57 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(const char *prefix_path, const char *suffix_path)
{
	char *const	tmp = ft_strjoin(prefix_path, FWD_SLASH_STR);
	char		*join;

	join = ft_strjoin(tmp, suffix_path);
	free(tmp);
	return (join);
}

static char	*join_path_without_backpath(
	const char *prefix,
	const char *suffix
	)
{
	char *const	alloc = malloc(PATH_MAX + 1);
	char		*new;
	char		*tmp;

	tmp = join_path(prefix, suffix);
	new = ft_realpath(tmp, alloc);
	free(tmp);
	return (new);
}

char	*clean_pwd(const char *new_pwd, const char *curr_path)
{
	return (join_path_without_backpath(curr_path, new_pwd));
}
