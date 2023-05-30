/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:13:20 by mat               #+#    #+#             */
/*   Updated: 2023/05/29 13:58:08 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_accessible(const char *path)
{
	return (access(path, F_OK) == 0
		&& access(path, X_OK) == 0);
}
