/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:34:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/22 15:37:11 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

void	init_shell(char **env)
{
	init_env(&g_global, env);
	set_catcher();
	init_tracker();
	check_pos(SHELL_INIT);
}
