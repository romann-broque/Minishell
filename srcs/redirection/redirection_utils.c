/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:15:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/19 15:20:08 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_out_fd(char *out, t_toktype tok_type)
{
	static int	perm_mask = (S_IRUSR | S_IWUSR)
		| (S_IRGRP | S_IWGRP)
		| (S_IROTH);
	int			mask;
	int			fd;

	mask = O_WRONLY;
	if (access(out, F_OK) != 0)
		mask |= O_CREAT;
	if (tok_type == T_RCHEVRON)
		mask |= O_TRUNC;
	else
		mask |= O_APPEND;
	fd = open(out, mask, perm_mask);
	if (fd == -1)
	{
		print_error("%s: %s: ", MINISHELL, out);
		perror(EMPTY_STR);
	}
	return (fd);
}

int	get_in_fd(char *in, t_toktype tok_type)
{
	int	fd;

	if (tok_type == T_DOUBLE_LCHEVRON)
		return (ft_heredoc(in));
	fd = INVALID_FD;
	if (access(in, F_OK) == 0)
		fd = open(in, O_RDONLY);
	if (fd == INVALID_FD)
	{
		print_error("%s: %s: ", MINISHELL, in);
		perror(EMPTY_STR);
	}
	return (fd);
}
