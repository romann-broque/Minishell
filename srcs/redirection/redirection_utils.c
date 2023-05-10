/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:15:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/10 15:20:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	ft_heredoc(char *end_str)
{
	int		fd_tmp;
	char	*line;
	char	*limiter;

	g_global.heredoc = true;
	limiter = ft_strjoin(end_str, NEWLINE_STR);
	fd_tmp = open(HDOC_TMP_FILE, O_RDWR | O_CREAT, 0644);
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
	close(fd_tmp);
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
	{
		in = HDOC_TMP_FILE;
		ft_heredoc(in);
	}
	if (access(in, F_OK) == 0)
	{
		fd = open(in, O_RDONLY);
	}
	if (fd == -1)
	{
		print_error("%s: %s: ", MINISHELL, in);
		perror(EMPTY_STR);
	}
	return (fd);
}
