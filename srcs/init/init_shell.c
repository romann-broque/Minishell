/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:34:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/15 00:40:49 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	init_pwd(void)
{
	char *const	curr_pwd = getcwd(NULL, 0);

	if (curr_pwd != NULL)
		update_cwd_var(curr_pwd);
	free(curr_pwd);
}

void	init_shell(char **env)
{
	init_env(&g_global, env);
	check_pos(SHELL_INIT);
	init_pwd();
	update_signal_state(S_DEFAULT);
	init_tracker();
}
