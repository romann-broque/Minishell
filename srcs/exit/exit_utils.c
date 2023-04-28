/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:45:04 by mat               #+#    #+#             */
/*   Updated: 2023/04/28 09:55:52 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//shifting the value 8 bits to the right and masking it with 0xFF

int	extract_return_status(int status)
{
	return ((status >> 8) & 0xFF);
}
