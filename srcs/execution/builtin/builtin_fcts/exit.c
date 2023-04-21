/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:48:25 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/20 22:03:08 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(__attribute__((unused)) t_command *cmd_data)
{
	free_manager();
	exit_shell(LAST_RETVAL);
}
