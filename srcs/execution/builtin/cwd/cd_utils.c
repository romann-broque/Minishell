/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:01:40 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/22 19:02:33 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_correct_size(char **command)
{
	size_t	cmd_size;

	cmd_size = 0;
	while (command[cmd_size])
		cmd_size++;
	if (cmd_size > CD_EXP_ARG)
	{
		print_error("%s: %s: %s\n", MINISHELL, CD_BUILTIN, TOO_MANY_ARGS);
		return (false);
	}
	return (true);
}

bool	is_prev_option(char **command)
{
	return (command[1] != NULL && streq(command[1], MINUS_SIGN) == true);
}
