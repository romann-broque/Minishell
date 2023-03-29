/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/29 18:20:29 by mdorr            ###   ########.fr       */
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

# define PROMPT			"minishell $ "
# define EXIT_MESSAGE	"exit"
# define WHITESPACES	" \t\n\v\f\r"
# define SEPARATORS		" \t\n"
# define LAST_RETVAL	EXIT_SUCCESS

/////////////////
/// FUNCTIONS ///
/////////////////

// exit_shell.c

void	exit_shell(const int exit_value);

// prompt.c

void	prompt(void);

// var.c

char	*expand_var(char *line);
char	*get_var_name(char *line);

// var2.c

void	fill_new_line(char *line, char *n_line, char *value, size_t n_l_len);

// signal.c

void	set_catcher(void);

// test_print.c

void	print_command(char **const command);

#endif
