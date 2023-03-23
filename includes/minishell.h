/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/23 12:48:22 by mat              ###   ########.fr       */
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
void	get_command(void);

// signal.c

void	set_catcher(void);

#endif
