/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:40:45 by mat               #+#    #+#             */
/*   Updated: 2023/04/03 17:46:16 by mat              ###   ########.fr       */
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
# define STR_LEN_MAX	50
# define WHITESPACES	" \t\n\v\f\r"
# define SEPARATORS		" \t\n"
# define S_QUOTE		'\''
# define D_QUOTE		'\"'
# define SPECIAL_VAR	"?0"
# define SPEC_VAR_LEN	2
# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'\"'
# define LAST_RETVAL	EXIT_SUCCESS

// Errors

# define SYNTAX_ERROR	"Syntax error"

//////////////////
/// STRUCTURES ///
//////////////////

typedef enum e_var_state
{
	E_STD,
	E_DOUBLE_QUOTE,
	E_SINGLE_QUOTE,
	E_DOLLAR,
	E_EOL
}			t_vstate;

typedef struct s_vmachine
{
	t_vstate	state;
	t_vstate	prev_state;
	size_t		word_len;
	size_t		i;
	char		*line;
}			t_vmachine;

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

//// VAR ////

// handle_var.c

// var_machine.c

// var_state_func.c

// var_utils.c

char	*expand_var(char *line);
void	reboot_vmachine(t_vmachine *const machine);
void	std_state(t_vmachine *const machine);
void	d_quote_state(t_vmachine *const machine);
void	s_quote_state(t_vmachine *const machine);
void	var_state(t_vmachine *const machine);
bool	is_in_var_charset(const char c);
bool	is_in_var_start_charset(const char c);
bool	is_special_var(const char c);
void	handle_var_start(t_vmachine *const machine);
void	translate_var(t_vmachine *const machine);
void	change_state(t_vstate new_state, t_vmachine *const machine);
char	*replace_and_free(
			char *src,
			char *replace,
			size_t index,
			size_t delete_len
			);

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
