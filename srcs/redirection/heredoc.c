/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:30:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/17 19:31:37 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (line != NULL && streq(end_str, line) == false
		&& g_global.s_state == S_INTERP)
	{
		ft_dprintf(fd_in, "%s\n", line);
		free(line);
		line = ft_readline(HD_PROMPT);
	}
	if (g_global.s_state == S_INTERP)
	{
		if (line == NULL)
			print_error("%s: %s: %s (wanted `%s')\n",
				MINISHELL, WARNING, HD_EOF_WARN, end_str);
	}
	free(line);
}

static int	process_heredoc(int hd_pipe[2], const char *end_str)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		g_global.pipe_in = hd_pipe[0];
		g_global.pipe_out = hd_pipe[1];
		fill_heredoc(hd_pipe[1], end_str);
		exit_shell(hd_pipe[0], false);
	}
	else
	{
		update_signal_state(S_SLEEP);
		wait(&status);
		if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGINT)
			return (WEXITSTATUS(status));
	}
	return (INVALID_FD);
}

int	ft_heredoc(char *end_str)
{
	int	hd_pipe[2];
	int	fd_hd;

	fd_hd = INVALID_FD;
	if (pipe(hd_pipe) == 0)
		fd_hd = process_heredoc(hd_pipe, end_str);
	else
	{
		print_error("%s: %s: ", MINISHELL, HERE_DOC);
		perror(EMPTY_STR);
		hd_pipe[0] = INVALID_FD;
	}
	close(hd_pipe[1]);
	return (fd_hd);
}
