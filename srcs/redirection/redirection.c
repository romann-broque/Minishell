/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:12:14 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 15:08:59 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	are_redirection_valid(t_command *cmd)
{
	return (cmd->fdin != INVALID_FD && cmd->fdout != INVALID_FD);
}

static void	change_output(
	t_command *curr_cmd,
	t_token *tok_redirect,
	t_toktype tok_type
	)
{
	if (curr_cmd->fdout != STDOUT_FILENO)
		close_safe(curr_cmd->fdout);
	if (are_redirection_valid(curr_cmd) == true)
	{
		if (tok_redirect->type == T_IDLE)
		{
			print_error("%s: %s\n", MINISHELL, AMB_REDIRECT);
			curr_cmd->fdin = INVALID_FD;
		}
		else
			curr_cmd->fdout = get_out_fd(tok_redirect->value, tok_type);
	}
}

static void	change_input(
	t_command *curr_cmd,
	t_token *tok_redirect,
	t_toktype tok_type
)
{
	if (curr_cmd->fdin != STDIN_FILENO)
		close_safe(curr_cmd->fdin);
	if (are_redirection_valid(curr_cmd) == true)
	{
		if (tok_redirect->type == T_IDLE)
		{
			print_error("%s: %s\n", MINISHELL, AMB_REDIRECT);
			curr_cmd->fdin = INVALID_FD;
		}
		else
			curr_cmd->fdin = get_in_fd(tok_redirect->value, tok_type);
	}
}

void	update_fds(t_toktype toktype, t_token *tok, t_command *cmd)
{
	if (toktype == T_RCHEVRON || toktype == T_DOUBLE_RCHEVRON)
		change_output(cmd, tok, toktype);
	else if (toktype == T_LCHEVRON || toktype == T_DOUBLE_LCHEVRON)
		change_input(cmd, tok, toktype);
}
