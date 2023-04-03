/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 14:58:26 by rbroque          ###   ########.fr       */
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
# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'\"'
# define LAST_RETVAL	EXIT_SUCCESS

// Errors

# define SYNTAX_ERROR	"Syntax error"

//////////////////
/// STRUCTURES ///
//////////////////

typedef enum e_quote_state
{
	E_SEPARATOR,
	E_QUOTE,
	E_DQUOTE,
	E_WORD,
	E_EOF
}			t_qstate;

typedef struct s_qmachine
{
	t_qstate	state;
	size_t		word_len;
	const char	*str;
	t_list		*tokens;
}				t_qmachine;

/////////////////
/// FUNCTIONS ///
/////////////////

//// EXIT ////

// exit_shell.c

void	exit_shell(const int exit_value);

//// PRINT ////

// print.c

void	print_command(char **const command);
void	print_error(const char *error_name);

//// PROMPT ////

// prompt.c

void	prompt(void);

//// SIGNAL ////

// signal.c

void	set_catcher(void);

//// TOKEN ////

// get_tokens.c

char	**get_tokens(const char *str);

// parse_states.c

void	separator_state(t_qmachine *const machine);
void	single_quote_state(t_qmachine *const machine);
void	double_quote_state(t_qmachine *const machine);
void	word_state(t_qmachine *const machine);

// strs_from_lst.c

char	**dup_strs_from_lst(t_list *lst);

// strs_to_lst.c

void	add_token(t_qmachine *machine);

// token_util.c

bool	is_separator(const char c);
void	update_state(t_qmachine *const machine);
void	init_qmachine(t_qmachine *const machine, const char *str);

// are_quotes_closed.c

bool	are_quotes_closed(const char *str);

#endif
