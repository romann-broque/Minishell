/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:59:54 by mat               #+#    #+#             */
/*   Updated: 2023/04/02 20:21:15 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_var_charset(char c)
{
	if (ft_isalnum((int)c) == 1 || c == '_')
		return (true);
	return (false);
}

bool	is_special_var(char c)
{
	if (c == '?' || c == '0' || c == '\0')
		return (true);
	else if (is_in_str(SEPARATORS, c) == 1)
		return (true);
	return (false);
}
