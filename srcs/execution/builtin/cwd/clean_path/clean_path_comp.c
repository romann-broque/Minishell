/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:58:56 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/25 17:11:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_next_tok(char *left, char *next_token, size_t *left_len)
{
	char	*p;
	char	*s;

	p = ft_strchr(left, FWD_SLASH);
	s = p;
	if (p == NULL)
		s = left + *left_len;
	if (s - left >= PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return (NULL);
	}
	ft_memcpy(next_token, left, s - left);
	next_token[s - left] = '\0';
	*left_len -= s - left;
	if (p != NULL)
		ft_memmove(left, s + 1, *left_len + 1);
	return (left);
}

static void	strip_comp(char *resolved, size_t *resolved_len)
{
	char	*ptr;

	if (*resolved_len > 1)
	{
		resolved[*resolved_len - 1] = '\0';
		ptr = ft_strrchr(resolved, FWD_SLASH) + 1;
		*ptr = '\0';
		*resolved_len = ptr - resolved;
	}
}

static char	*process_comp(
	char *left,
	size_t *left_len,
	char *resolved,
	size_t *resolved_len
	)
{
	char	next_token[PATH_MAX];

	if (extract_next_tok(left, next_token, left_len) == NULL)
		return (NULL);
	if (resolved[*resolved_len - 1] != FWD_SLASH)
	{
		if (*resolved_len + 1 >= PATH_MAX)
		{
			errno = ENAMETOOLONG;
			return (NULL);
		}
		*resolved_len = ft_strlcat(resolved, FWD_SLASH_STR, PATH_MAX);
	}
	if (streq(next_token, DOUBLE_DOT_STR) == true)
		strip_comp(resolved, resolved_len);
	else if (next_token[0] != '\0' && streq(next_token, DOT_STR) == false)
	{
		*resolved_len = ft_strlcat(resolved, next_token, PATH_MAX);
		if (*resolved_len >= PATH_MAX)
		{
			errno = ENAMETOOLONG;
			return (NULL);
		}
	}
	return (left);
}

char	*clean_path_comp(
	char *left,
	size_t *left_len,
	char *resolved,
	size_t *resolved_len
	)
{
	while (*left_len > 0)
	{
		if (process_comp(left, left_len, resolved, resolved_len) == NULL)
			return (NULL);
	}
	return (left);
}
