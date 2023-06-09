/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:16:24 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/30 14:52:27 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_line(void)
{
	rl_on_new_line();
	rl_replace_line(EMPTY_STR, 0);
	rl_redisplay();
}

void	add_line_to_history(const char *line)
{
	if (line != NULL && *line != '\0')
		add_history(line);
}

char	*get_line(__attribute__((unused)) const char *prompt)
{
	char *const	line = get_next_line(STDIN_FILENO);
	char		*new_line_ptr;

	if (line != NULL)
	{
		new_line_ptr = ft_strchr(line, NEWLINE);
		if (new_line_ptr != NULL)
			*new_line_ptr = '\0';
	}
	return (line);
}

t_reader	get_reader_fct(const int is_interactive)
{
	(void)is_interactive;
	return (readline);
}
	// if (is_interactive == 1)
	// return (get_line);
