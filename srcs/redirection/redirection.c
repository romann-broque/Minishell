/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:12:14 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/10 14:24:22 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	change_input(
	t_command *curr_cmd,
	char *tok_value,
	t_toktype tok_type
)
{
	if (curr_cmd->fdin != STDIN_FILENO)
		close(curr_cmd->fdin);
	curr_cmd->fdin = get_in_fd(tok_value, tok_type);
}

void	update_fds(t_toktype toktype, t_token *tok, t_command *cmd)
{
	if (toktype == T_RCHEVRON || toktype == T_DOUBLE_RCHEVRON)
		change_output(cmd, tok->value, toktype);
	if (toktype == T_LCHEVRON || toktype == T_DOUBLE_LCHEVRON)
		change_input(cmd, tok->value, toktype);
}
