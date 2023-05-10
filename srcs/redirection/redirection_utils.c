/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:15:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/10 14:21:29 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	ft_heredoc(char *end_str)
{
	int		fd_tmp;
	char	*line;
	char	*limiter;

	g_global.heredoc = true;
	limiter = ft_strjoin(end_str, NEWLINE_STR);
	fd_tmp = open(HDOC_TMP_FILE, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || (ft_strlen(limiter) == ft_strlen(line)
				&& streq(limiter, line) == true))
			break ;
		write(fd_tmp, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	return (fd_tmp);
}

int	get_out_fd(char *out, t_toktype tok_type)
{
	static int	perm_mask = (S_IRUSR | S_IWUSR)
		| (S_IRGRP | S_IWGRP)
		| (S_IROTH);
	int			mask;
	int			fd;

	mask = O_RDWR;
	if (access(out, F_OK) != 0)
		mask |= O_CREAT;
	if (tok_type == T_RCHEVRON)
		mask |= O_TRUNC;
	else
		mask |= O_APPEND;
	fd = open(out, mask, perm_mask);
	if (fd == -1)
		perror(EMPTY_STR);
	return (fd);
}

int	get_in_fd(char *in, t_toktype tok_type)
{
	int	fd;

	fd = -1;
	if (tok_type == T_DOUBLE_LCHEVRON)
		return (ft_heredoc(in));
	else
	{
		if (access(in, F_OK | R_OK) == -1)
			perror(EMPTY_STR);
		else
			fd = open(in, O_RDONLY);
		return (fd);
	}
}
