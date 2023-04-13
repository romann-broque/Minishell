/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:53:17 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/13 11:38:11 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_in_strs(const char **strs, const char *str)
{
	while (*strs != NULL && streq(*strs, str) == false)
		++strs;
	return (*strs != NULL);
}

bool	is_builtin(t_command *cmd_data)
{
	static const char	*builtin_array[] = {
		CD_BUILTIN,
		ECHO_BUILTIN,
		EXIT_BUILTIN,
		EXPORT_BUILTIN,
		PWD_BUILTIN,
		UNSET_BUILTIN,
		NULL
	};
	const char			*cmd_name = cmd_data->command[0];

	return (is_in_strs(builtin_array, cmd_name));
}
