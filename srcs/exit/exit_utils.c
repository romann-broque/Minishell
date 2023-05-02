/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:45:04 by mat               #+#    #+#             */
/*   Updated: 2023/04/30 16:44:21 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

//shifting the value 8 bits to the right and masking it with 0xFF

int	extract_return_status(const int status)
{
	return ((status >> 8) & 0xFF);
}

void	update_error_val(const int error_nbr)
{
	g_global.last_ret_val = error_nbr;
}
