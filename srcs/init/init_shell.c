/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:34:28 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 13:03:44 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	init_pwd(void)
{
	char *const	curr_pwd = getcwd(NULL, 0);
	char		*old_pwd;

	if (curr_pwd != NULL)
	{
		add_deallocator(curr_pwd, free);
		init_cwd_var(curr_pwd);
		old_pwd = ft_getenv(OLDPWD_VAR);
		if (streq(old_pwd, EMPTY_STR) == true)
			set_var_flag(OLDPWD_VAR, SLEEP_MASK);
	}
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

	if (lvl_str == NULL)
		exit_alloc();
	update_var(SHLVL_VAR, lvl_str, SLEEP_MASK);
	free(lvl_str);
}

static void	init_fds(void)
{
	g_global.stdin = dup(STDIN_FILENO);
	g_global.stdout = dup(STDOUT_FILENO);
	g_global.hd_pipe[0] = INVALID_FD;
	g_global.hd_pipe[1] = INVALID_FD;
	g_global.prev_pipe = INVALID_FD;
}

void	init_shell(char **env)
{
	update_signal_state(S_SLEEP);
	init_tracker();
	init_env(&g_global, env);
	g_global.pid_lst = NULL;
	g_global.is_stopped = false;
	init_fds();
	check_pos(SHELL_INIT);
	init_pwd();
	init_shlvl();
	update_signal_state(S_DEFAULT);
}
