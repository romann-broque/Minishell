/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:12:14 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/09 12:01:57 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_out_fd(char *out, t_toktype tok_type)
{
	int	fd;
	int	mask;

	mask = O_WRONLY;
	if (access(out, F_OK) != 0)
		mask |= O_CREAT;
	if (tok_type == T_RCHEVRON)
		mask |= O_TRUNC;
	else
		mask |= O_APPEND;
	fd = open(out, mask);
	if (fd == -1)
		perror(EMPTY_STR);
	return (fd);
}

static void	change_output(
	t_command *curr_cmd,
	char *tok_value,
	t_toktype tok_type
	)
{
	if (curr_cmd->fdout != STDOUT_FILENO)
		close(curr_cmd->fdout);
	curr_cmd->fdout = get_out_fd(tok_value, tok_type);
}

void	update_fds(t_toktype toktype, t_token *tok, t_command *cmd)
{
	if (toktype == T_RCHEVRON || toktype == T_DOUBLE_RCHEVRON)
		change_output(cmd, tok->value, toktype);
}
