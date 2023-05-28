/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:19:40 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/28 13:12:55 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static char	*ft_readline(const char *prompt)
{
	char	*line;

	ft_dprintf(STDIN_FILENO, prompt);
	line = get_next_line(STDIN_FILENO);
	if (line != NULL && line[0] != '\0')
		line[ft_strlen(line + 1)] = '\0';
	return (line);
}

static void	fill_heredoc(const int fd_in, const char *end_str)
{
	char	*line;

	line = ft_readline(HD_PROMPT);
	while (line != NULL && streq(end_str, line) == false)
	{
		ft_dprintf(fd_in, "%s\n", line);
		free(line);
		line = ft_readline(HD_PROMPT);
	}
	if (line == NULL)
		print_error("%s: %s: %s (wanted `%s')\n",
			MINISHELL, WARNING, HD_EOF_WARN, end_str);
	free(line);
}

static int	hd_parent_waiting(const int fd)
{
	int	exit_status;
	int	status;

	update_signal_state(S_SLEEP);
	wait(&status);
	exit_status = WEXITSTATUS(status);
	g_global.last_ret_val = exit_status;
	if (exit_status == SIGINT_RETVAL)
		return (INVALID_FD);
	return (fd);
}

static int	process_heredoc(int hd_pipe[2], const char *end_str)
{
	if (fork() == 0)
	{
		ft_memcpy(g_global.hd_pipe, hd_pipe, 2 * sizeof(int));
		update_signal_state(S_HEREDOC);
		fill_heredoc(hd_pipe[1], end_str);
		exit_shell(EXIT_SUCCESS, false);
	}
	return (hd_parent_waiting(hd_pipe[0]));
}

int	ft_heredoc(const char *end_str)
{
	int	hd_pipe[2];
	int	fd_hd;

	fd_hd = INVALID_FD;
	if (pipe(hd_pipe) == 0)
		fd_hd = process_heredoc(hd_pipe, end_str);
	else
		print_error("%s: %s: %s\n", MINISHELL, HERE_DOC, strerror(errno));
	close(hd_pipe[1]);
	return (fd_hd);
}
