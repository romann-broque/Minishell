/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:51:57 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/29 15:52:20 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_separator(const char c)
{
	return (ft_strchr(SEPARATORS, c));
}

bool	is_last_quote(t_qmachine *machine, const char quote)
{
	const char	*str = machine->str - machine->word_len;
	bool		is_end;
	size_t		i;

	is_end = false;
	i = 0;
	while (i < machine->word_len)
	{
		if (str[i] == quote)
		{
			if (is_end == false && is_separator(str[i + 1]) == true)
				is_end = true;
			else
				is_end = false;
		}
		++i;
	}
	return ((str[i] == '\0' || str[i + 1] != quote) && is_end);
}
