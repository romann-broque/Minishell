/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:15:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/11 11:16:05 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	ft_heredoc(char *end_str)
{
	char	*line;
	char	*limiter;
	int		hd_pipe[2];

	pipe(hd_pipe);
	limiter = ft_strjoin(end_str, NEWLINE_STR);
	while (1)
	{
		ft_dprintf(STDIN_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || (streq(limiter, line) == true))
		{
			free(line);
			break ;
		}
		ft_dprintf(hd_pipe[1], line);
		free(line);
	}
	free(limiter);
	close(hd_pipe[1]);
	return (hd_pipe[0]);
}

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

	fd = -1;
	if (tok_type == T_DOUBLE_LCHEVRON)
		return (ft_heredoc(in));
	if (access(in, F_OK) == 0)
		fd = open(in, O_RDONLY);
	if (fd == -1)
	{
		print_error("%s: %s: ", MINISHELL, in);
		perror(EMPTY_STR);
	}
	return (fd);
}
