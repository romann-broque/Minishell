/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:24 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/11 11:09:38 by rbroque          ###   ########.fr       */
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

// string

# define PROMPT			"minishell $ "
# define EXIT_MESSAGE	"exit"
# define QMARK_VAR		"LAST_RET_VAL"
# define ZERO_VAR		"minishell"

// tok_string

# define LCHEVRON			"<"
# define RCHEVRON			">"
# define DOUBLE_LCHEVRON	"<<"
# define DOUBLE_RCHEVRON	">>"
# define PIPE				"|"
# define OR					"||"
# define AND				"&&"

// error string

# define SYNTAX_ERROR	"Syntax error"
# define MALLOC_ERROR	"Malloc error"
# define PARS_ERROR		"Parsing error"

// char types

# define TOK_LEXEME		"<>|&"
# define WHITESPACES	" \t\n\v\f\r"
# define SEPARATORS		" \t\n"
# define SPECIAL_VAR	"?0"
# define EMPTY_STR		""

// char

# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'\"'
# define DOLLAR_SIGN	'$'
# define UNDERSCORE		'_'
# define AMPERSAND		'&'
# define EQUAL_SIGN		'='

// len

# define STR_LEN_MAX	50
# define SPEC_VAR_LEN	2
# define WRONG_VAR_LEN	2
# define MAX_LEN_TYPE	2

// count

# define NEXT_TOK_MAX	9

// return value

# define LAST_RETVAL	EXIT_SUCCESS

// enum

# define ASSIGN_START	0

//////////////////
/// STRUCTURES ///
//////////////////

typedef enum e_toktype
{
	T_LCHEVRON,
	T_RCHEVRON,
	T_DOUBLE_LCHEVRON,
	T_DOUBLE_RCHEVRON,
	T_PIPE,
	T_OR,
	T_AND,
	T_ASSIGN,
	T_GENERIC,
	T_START,
	T_END,
	T_INVALID
}			t_toktype;

typedef struct s_token
{
	t_toktype	type;
	char		*value;
}				t_token;

typedef enum e_var_state
{
	E_STD,
	E_DOUBLE_QUOTE,
	E_SINGLE_QUOTE,
	E_SPEC_VAR,
	E_VAR,
	E_EOL
}			t_vstate;

typedef struct s_vmachine
{
	t_vstate	state;
	t_vstate	prev_state;
	size_t		word_len;
	size_t		index;
	char		*line;
}			t_vmachine;

typedef enum e_quote_state
{
	E_SEPARATOR,
	E_QUOTE,
	E_DQUOTE,
	E_SPEC_TOK,
	E_WORD,
	E_EOF
}			t_qstate;

typedef struct s_qmachine
{
	t_qstate	state;
	size_t		word_len;
	const char	*str;
	t_list		*words;
}				t_qmachine;

typedef struct s_tokparse
{
	t_toktype	curr;
	t_toktype	next[NEXT_TOK_MAX];
}			t_tokparse;

/////////////////
/// FUNCTIONS ///
/////////////////

//			EXIT			//

/// exit_shell.c

void		exit_shell(const int exit_value);

//			EXPANSION			//

// expand_command.c

void		expand_command(t_list *tokens);

///  VAR  ///

//// handle_var.c

void		replace_special_var(t_vmachine *const machine);
void		handle_var_start(t_vmachine *const machine);
void		translate_var(t_vmachine *const machine);

//// var_machine.c

char		*expand_var(const char *line);
void		change_state(t_vstate new_state, t_vmachine *const machine);

//// var_state_func.c

void		std_state(t_vmachine *const machine);
void		d_quote_state(t_vmachine *const machine);
void		s_quote_state(t_vmachine *const machine);
void		spec_var_state(t_vmachine *const machine);
void		var_state(t_vmachine *const machine);

//// var_utils.c

bool		is_in_var_charset(const char c);
bool		is_in_var_start_charset(const char c);
bool		is_special_var(const char c);
char		*cut_string_at(char *src, const size_t index, const size_t del_len);
void		delete_quote(t_vmachine *const machine);

//			LEXER			//

///  QUOTES  ///

//// are_quotes_closed.c

bool		are_quotes_closed(const char *str);

///  TOKENS  ///

//// lexer.c

t_list		*lexer_root(const char *str);
t_list		*lexer(const char *str);

// assign_states_utils.c

void		update_state_assign(const char c, t_qstate *state);
bool		is_assign(const char *word);

// assign_states.c

bool		start_state_assign(const char **word, t_qstate *state);
bool		word_state_assign(const char **word, t_qstate *state);
bool		squote_state_assign(const char **word, t_qstate *state);
bool		dquote_state_assign(const char **word, t_qstate *state);

//// token_utils.c

t_token		*init_token(t_toktype type, char *value);
char		*get_str_from_tok(t_token *tok);
void		free_token(t_token *tok);

//// tokenizer.c

t_list		*tokenizer(t_list *words);

///  WORD  ///

//// get_words.c

t_list		*get_words(const char *str);

//// parse_states.c

void		separator_state(t_qmachine *const machine);
void		single_quote_state(t_qmachine *const machine);
void		double_quote_state(t_qmachine *const machine);
void		spec_tok_state(t_qmachine *const machine);
void		word_state(t_qmachine *const machine);

//// strs_to_lst.c

void		add_token(t_qmachine *machine);
void		add_spec_token(t_qmachine *machine,
				const char spec_tok[][MAX_LEN_TYPE + 1]);

//// word_utils.c

bool		is_separator(const char c);
void		update_state(t_qmachine *const machine);
void		init_qmachine(t_qmachine *const machine, const char *str);
void		quote_state(t_qmachine *const machine, const char quote);

//			PARSER			//

/// parser.c

bool		parser(t_list *tokens);

//			PRINT			//

/// print.c

void		print_command(t_list *token_lst);
void		print_error(const char *error_name);

//			PROMPT			//

/// prompt.c

void		prompt(void);

//			SIGNAL			//

/// signal.c

void		set_catcher(void);

#endif
