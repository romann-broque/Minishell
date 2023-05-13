/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:15:11 by mat               #+#    #+#             */
/*   Updated: 2023/05/13 11:17:15 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	fill_heredoc(const int fd_in, const char *end_str)
{
	char	*line;

	line = readline(HD_PROMPT);
	while (line != NULL && streq(end_str, line) == false)
	{
		ft_dprintf(fd_in, "%s\n", line);
		free(line);
		line = readline(HD_PROMPT);
	}
	if (line == NULL)
		print_error("%s: %s: %s (wanted `%s')\n",
			MINISHELL, WARNING, HD_EOF_WARN, end_str);
	free(line);
}

static int	ft_heredoc(char *end_str)
{
	int	hd_pipe[2];

	pipe(hd_pipe);
	fill_heredoc(hd_pipe[1], end_str);
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
