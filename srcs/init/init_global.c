/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:42:57 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 18:09:01 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_fds(t_global *glob)
{
	glob->stdin = dup(STDIN_FILENO);
	glob->stdout = dup(STDOUT_FILENO);
	glob->hd_pipe[0] = INVALID_FD;
	glob->hd_pipe[1] = INVALID_FD;
	glob->prev_pipe = INVALID_FD;
	if (glob->stdin == INVALID_FD
		|| glob->stdout == INVALID_FD)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_global	*init_global(void)
{
	t_global	*new;

	new = (t_global *)malloc(sizeof(t_global));
	if (new != NULL)
	{
		if (init_fds(new) == EXIT_FAILURE)
			exit_shell(EXIT_FAILURE, false);
		new->garbage = NULL;
		new->env = NULL;
		new->pid_lst = NULL;
		new->cmd_lst = NULL;
		new->cmd_nbr = 0;
		new->cmd_index = 0;
		new->is_stopped = false;
		new->last_ret_val = EXIT_SUCCESS;
	}
	return (new);
}
