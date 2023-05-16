/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:34:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/16 15:48:45 by mdorr            ###   ########.fr       */
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
		if (old_pwd == NULL || streq(old_pwd, EMPTY_STR) == true)
			set_var_flag(OLDPWD_VAR, SLEEP_MASK);
	}
	free(curr_pwd);
}

static int	get_shlvl_value(void)
{
	const char	*shlvl_value = ft_getenv(SHLVL_VAR);

	if (shlvl_value == NULL)
		shlvl_value = SHLVL_DEFAULT;
	return (ft_atoi(shlvl_value) + 1);
}

static void	init_shlvl(void)
{
	const int	lvl = get_shlvl_value();
	char *const	lvl_str = ft_itoa(lvl);

	change_var(SHLVL_VAR, lvl_str, SLEEP_MASK, &g_global.env);
	free(lvl_str);
}

void	init_shell(char **env)
{
	init_env(&g_global, env);
	check_pos(SHELL_INIT);
	init_pwd();
	init_shlvl();
	set_catcher();
	init_tracker();
}
