/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:45:04 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 10:31:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

int	extract_return_status(const int status)
{
	return (WEXITSTATUS(status));
}

void	update_error_val(const int error_nbr)
{
	g_global.last_ret_val = error_nbr;
}
