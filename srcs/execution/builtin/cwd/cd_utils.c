/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:01:40 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/25 22:58:27 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_correct_size(char **command)
{
	size_t	cmd_size;

	cmd_size = 0;
	while (command[cmd_size])
		cmd_size++;
	return (cmd_size <= CD_EXP_ARG);
}

bool	is_prev_option(char **command)
{
	return (command[1] != NULL && streq(command[1], MINUS_SIGN) == true);
}
