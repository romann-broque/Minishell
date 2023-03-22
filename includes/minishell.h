/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/22 16:12:29 by rbroque          ###   ########.fr       */
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

///////////////
/// DEFINES ///
///////////////

# define PROMPT "minishell $ "
# define EXIT_MESSAGE "exit"
# define WHITESPACES " \t\n\v\f\r"
# define SEPARATORS " \t\n"

/////////////////
/// FUNCTIONS ///
/////////////////

// exit_print.c

void	exit_shell(const int exit_value);

// prompt.c

void	prompt(void);

#endif
