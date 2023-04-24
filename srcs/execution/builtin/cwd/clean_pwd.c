/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:16 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/24 18:02:24 by rbroque          ###   ########.fr       */
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

char	*ft_remove_neighboor(const char *str, const char *charset)
{
	const size_t	len = get_rm_neighboor_len(str, charset);
	char			*new;

	new = (char *)malloc((len + 1) * sizeof(char));
	if (new != NULL)
		cpy_rm_neighboor(new, str, charset);
	return (new);
}

char	*get_clean_pwd_value(const char *new_pwd, const char *curr_path)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin(curr_path, FWD_SLASH_STR);
	new = ft_strjoin(tmp, new_pwd);
	free(tmp);
	if (ft_strstr(new, "/..") != NULL)
		tmp = get_clean_path(new);
	else
		tmp = ft_strdup(new);
	free(new);
	new = ft_remove_neighboor(tmp, FWD_SLASH_STR);
	free(tmp);
	return (new);
}
