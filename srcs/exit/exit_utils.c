/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:45:04 by mat               #+#    #+#             */
/*   Updated: 2023/04/28 14:52:08 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

//shifting the value 8 bits to the right and masking it with 0xFF

int	extract_return_status(int status)
{
	return ((status >> 8) & 0xFF);
}

void	update_cmd_error_val(bool accessible)
{
	if (accessible == true)
		g_global.last_ret_val = 127;
	else
		g_global.last_ret_val = 126;
}
