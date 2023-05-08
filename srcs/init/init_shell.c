/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:34:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/08 11:09:38 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

static void	init_pwd(void)
{
	char *const	curr_pwd = getcwd(NULL, 0);
	char		*old_pwd;

	if (curr_pwd != NULL)
	{
		update_cwd_var(curr_pwd);
		old_pwd = ft_getenv(OLDPWD_VAR);
		if (old_pwd != NULL && streq(old_pwd, EMPTY_STR) == true)
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
