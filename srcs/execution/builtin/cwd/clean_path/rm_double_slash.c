/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_double_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:27:34 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/25 18:00:27 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_rm_neighboor_len(const char *str, const char *charset)
{
	size_t	len;
	bool	is_in_charset;

	len = 0;
	is_in_charset = false;
	while (*str != '\0')
	{
		if (is_in_str(charset, *str) == true)
		{
			len += (is_in_charset == false);
			is_in_charset = true;
		}
		else
		{
			is_in_charset = false;
			++len;
		}
		++str;
	}
	return (len);
}

static void	cpy_rm_neighboor(char *dest, const char *src, const char *charset)
{
	size_t	i;
	bool	is_in_charset;

	is_in_charset = false;
	i = 0;
	while (*src != '\0')
	{
		if (is_in_str(charset, *src) == true)
		{
			if (is_in_charset == false)
			{
				dest[i] = *src;
				++i;
			}
			is_in_charset = true;
		}
		else
		{
			dest[i] = *src;
			++i;
			is_in_charset = false;
		}
		++src;
	}
	dest[i] = '\0';
}

static char	*ft_remove_neighboor(const char *str, const char *charset)
{
	const size_t	len = get_rm_neighboor_len(str, charset);
	char			*new;

	new = (char *)malloc((len + 1) * sizeof(char));
	if (new != NULL)
		cpy_rm_neighboor(new, str, charset);
	return (new);
}

char	*rm_double_slash(const char *str)
{
	char *const	slash_str = ft_remove_neighboor(str, FWD_SLASH_STR);
	size_t		len;

	if (slash_str != NULL)
	{
		len = ft_strlen(slash_str);
		silent_trailing_slash(slash_str, len);
	}
	return (slash_str);
}
