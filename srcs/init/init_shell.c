/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:34:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 18:40:27 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

static void	init_pwd(void)
{
	char *const	curr_pwd = getcwd(NULL, 0);

	if (curr_pwd != NULL)
	{
		update_cwd_var(curr_pwd);
		if (streq(ft_getenv(OLDPWD_VAR), EMPTY_STR) == true)
			set_var_flag(OLDPWD_VAR, SLEEP_MASK);
	}
	free(curr_pwd);
}

void	init_shell(char **env)
{
	init_env(&g_global, env);
	check_pos(SHELL_INIT);
	init_pwd();
	set_catcher();
	init_tracker();
}
