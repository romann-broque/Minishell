/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:15:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/30 14:42:51 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_out_fd(int *fd, char *out, t_toktype tok_type)
{
	static int	perm_mask = (S_IRUSR | S_IWUSR)
		| (S_IRGRP | S_IWGRP)
		| (S_IROTH);
	int			mask;
	int			new_fd;

	mask = O_WRONLY;
	if (access(out, F_OK) != 0)
		mask |= O_CREAT;
	if (tok_type == T_RCHEVRON)
		mask |= O_TRUNC;
	else
		mask |= O_APPEND;
	new_fd = open(out, mask, perm_mask);
	if (new_fd == -1)
		print_error("%s: %s: %s\n", MINISHELL, out, strerror(errno));
	if (isatty(new_fd))
		close(new_fd);
	else
		*fd = new_fd;
}

void	get_in_fd(int *fd, char *in, t_toktype tok_type)
{
	int	new_fd;

	if (tok_type == T_DOUBLE_LCHEVRON)
		*fd = ft_heredoc(in);
	else
	{
		new_fd = INVALID_FD;
		if (access(in, F_OK) == 0)
			new_fd = open(in, O_RDONLY);
		if (new_fd == INVALID_FD)
			print_error("%s: %s: %s\n", MINISHELL, in, strerror(errno));
		if (isatty(new_fd))
			close(new_fd);
		else
			*fd = new_fd;
	}
}
