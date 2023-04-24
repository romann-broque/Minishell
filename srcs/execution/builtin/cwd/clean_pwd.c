/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:16 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/24 22:15:39 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(const char *prefix_path, const char *suffix_path)
{
	char	*tmp;
	char	*join;

	tmp = ft_strjoin(prefix_path, FWD_SLASH_STR);
	join = ft_strjoin(tmp, suffix_path);
	free(tmp);
	return (join);
}

static char	*join_path_without_backpath(
	const char *prefix,
	const char *suffix
	)
{
	char	*new;
	char	*tmp;

	tmp = join_path(prefix, suffix);
	new = rm_backpath(tmp);
	free(tmp);
	return (new);
}

char	*clean_pwd(const char *new_pwd, const char *curr_path)
{
	char	*tmp;
	char	*new;

	tmp = join_path_without_backpath(curr_path, new_pwd);
	printf("tmp --> [%s]\n", tmp);
	new = rm_double_slash(tmp);
	free(tmp);
	return (new);
}
