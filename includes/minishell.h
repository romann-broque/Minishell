/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/30 14:18:08 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////
/// INCLUDES ///
////////////////

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

///////////////
/// DEFINES ///
///////////////

# define MALLOC_ERROR	"Malloc error"
# define PROMPT			"minishell $ "
# define EXIT_MESSAGE	"exit"
# define WHITESPACES	" \t\n\v\f\r"
# define SEPARATORS		" \t\n"
# define LAST_RETVAL	EXIT_SUCCESS

/////////////////
/// FUNCTIONS ///
/////////////////

// exit_shell

void	exit_shell(const int exit_value);

// prompt

void	prompt(void);

// var

char	*expand_var(char *line);
void	fill_new_line(char *line, char *n_line, char *value, size_t n_l_len);
size_t	get_var_len(char *line, ssize_t index);
size_t	get_special_len(char *line, ssize_t index);
bool	is_special_character(char c);

// signal

void	set_catcher(void);

// print

void	print_command(char **const command);

#endif
