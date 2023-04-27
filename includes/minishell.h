/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:24 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/27 17:19:36 by mat              ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

///////////////
/// DEFINES ///
///////////////

// string

# define MINISHELL		"minishell"
# define PROMPT			"minishell $ "
# define EXIT_MESSAGE	"exit"
# define QMARK_VAR		"LAST_RET_VAL"
# define ZERO_VAR		"minishell"
# define FWD_SLASH_STR	"/"
# define DOT_STR		"."
# define DOUBLE_DOT_STR	".."
# define BATCH_OPT		"-c"
# define BACKPATH		"/.."

// builtins

# define CD_BUILTIN		"cd"
# define ECHO_BUILTIN	"echo"
# define EXIT_BUILTIN	"exit"
# define EXPORT_BUILTIN	"export"
# define PWD_BUILTIN	"pwd"
# define UNSET_BUILTIN	"unset"

// fct

# define GETCWD			"getcwd"
# define CHDIR			"chdir"
# define SHELL_INIT		"shell-init"

// env

# define HOME_VAR		"HOME"
# define OLDPWD_VAR		"OLDPWD"
# define PWD_VAR		"PWD"
# define PATH_VAR		"PATH"
# define CDPATH_VAR		"CDPATH"

// tok_string

# define LCHEVRON			"<"
# define RCHEVRON			">"
# define DOUBLE_LCHEVRON	"<<"
# define DOUBLE_RCHEVRON	">>"
# define PIPE				"|"
# define OR					"||"
# define AND				"&&"
# define END_STR			"newline"

// error string

# define SYNTAX_ERROR		"Syntax error"
# define MALLOC_ERROR		"Malloc error"
# define PARS_ERROR			"syntax error near unexpected token"
# define CMD_NOT_FOUND		"command not found"
# define IS_DIR				"Is a directory"
# define STAT_ERROR			"Failed to stat file"
# define TOO_MANY_ARGS		"too many arguments"
# define ERROR_ACCESS_DIR		"error retrieving current directory"
# define ERROR_ACCESS_PAR_DIR	"cannot access parent directories"

// char types

# define TOK_LEXEME		"<>|&"
# define WHITESPACES	" \t\n\v\f\r"
# define SEPARATORS		" \t\n"
# define SPECIAL_VAR	"?0"
# define EMPTY_STR		""
# define EQUAL_SIGN_STR	"="
# define TIELD			"~"

// char

# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'\"'
# define DOLLAR_SIGN	'$'
# define UNDERSCORE		'_'
# define AMPERSAND		'&'
# define EQUAL_SIGN		'='
# define FWD_SLASH		'/'
# define COLON			':'
# define DOT			'.'

// len

# define SPEC_VAR_LEN	2
# define WRONG_VAR_LEN	2
# define BACKPATH_LEN	3

// count

# define NEXT_TOK_MAX	11
# define NB_DEALLOCATOR	5
# define CD_EXP_ARG		2

// return value

# define IGNORE_TOK		1
# define LAST_RETVAL	EXIT_SUCCESS

// enum

# define ASSIGN_START	0

/////////////
/// ENUM ///
/////////////

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
	T_INVALID,
	T_VAR
}			t_toktype;

typedef enum e_var_state
{
	E_STD,
	E_DOUBLE_QUOTE,
	E_SINGLE_QUOTE,
	E_SPEC_VAR,
	E_VAR,
	E_EOL
}			t_vstate;

typedef enum e_quote_state
{
	E_SEPARATOR,
	E_QUOTE,
	E_DQUOTE,
	E_SPEC_TOK,
	E_WORD,
	E_EOF
}			t_qstate;

//////////////////
/// STRUCTURES ///
//////////////////

typedef struct s_token
{
	t_toktype	type;
	char		*value;
}				t_token;

typedef struct s_vmachine
{
	t_vstate	state;
	t_vstate	prev_state;
	size_t		word_len;
	size_t		index;
	char		*line;
}				t_vmachine;

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
}				t_tokparse;

typedef struct s_command
{
	char	**command;
	char	**env;
	int		fdin;
	int		fdout;
}				t_command;

typedef struct s_deallocator
{
	void	*ptr;
	void	(*free_fct)(void *);
}				t_deallocator;

typedef struct s_resource_tracker
{
	t_deallocator	deallocator_array[NB_DEALLOCATOR];
	size_t			index;
}				t_resource_tracker;

typedef struct s_builtin_mapper
{
	const char	*name;
	void		(*fct)(t_command *cmd_data);
}				t_builtin_mapper;

typedef struct s_global
{
	t_resource_tracker	tracker;
	char				**env;
	int					last_ret_val;
	bool				is_stoppable;
}				t_global;

/////////////////
/// FUNCTIONS ///
/////////////////

//			BATCH				//

///	batch.c

bool		batch_mode(int ac, char **av);
void		exec_batch(int ac, char **av);

//			ENV					//

/// change_var.c

void		change_var(const char *var_name, const char *var_value);

/// ft_getenv.c

char		*ft_getenv(const char *var_name);

/// init_env.c

size_t		get_size_strs(char **strs);
void		cpy_strs(char **dest, char **src);
void		init_env(t_global *global, char **env);

///			PATH				///

//// clean_path.c

void		clean_path(char **path);

//// get_path.c

bool		is_cmd_path(t_command *cmd);
char		*get_path_from_cmd(t_command *cmd);
char		*get_path_from_env(const char *suffix,
				const char *pathvar_name, char **env);

//// cmd_path_utils.c

void		add_fwd_slash(char **paths);
bool		is_var_path_in_env(char **env, const char *pathvar_name);
bool		is_empty_str(const char *str);
bool		is_path_var(const char *env_line, const char *pathvar_name);

//			EXECUTION			//

/// execution.c

void		execution(t_command *command);

///  BUILTIN  ///

//// exec_buitlin.c

void		exec_builtin(t_command *command);

//// is_builtin.c

bool		is_builtin(t_command *cmd_data);

////  BUILTIN_FCTS  ////

///// cd.c

void		cd_builtin(t_command *cmd_data);

///// echo.c

void		echo_builtin(t_command	*cmd_data);

///// exit.c

void		exit_builtin(t_command *cmd_data);

///// pwd.c

void		pwd_builtin(__attribute__((unused)) t_command *cmd_data);

////  CWD  ////

//// cd_arg.c

char		*get_cd_arg(t_command *cmd_data, const char *arg, bool *is_print);

//// cd_utils.c

bool		is_correct_size(char **command);
bool		is_prev_option(char **command);

/// cwd_utils.c

char		*ft_strstr(const char *big, const char *little);
void		check_pos(const char *caller);
void		update_cwd_var(const char *new_pwd);
int			print_pos(void);

/// CLEAN_PATH ///

//// clean_pwd.c

char		*clean_pwd(const char *new_pwd, const char *curr_path);

//// ft_realpath_utils.c

char		*clean_path_comp(char *left, size_t *left_len,
				char *resolved, size_t *resolved_len);

//// ft_realpath.c

void		silent_trailing_slash(char *str, const size_t len);
char		*ft_realpath(const char *path);

//			EXIT			//

/// exit_shell.c

void		exit_shell(const int exit_value);

/// exit_utils.c

int			extract_return_status(int status);

//			EXPANSION			//

/// expand_command.c

void		expand_command(t_list **tokens);

/// rm_empty_var.c

void		flag_var(t_list *tokens);
void		rm_empty_var(t_list **tokens);

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

//			FREE			//

// free_manager.c

void		free_command_lst(void *ptr);
void		free_token_lst(void *ptr);
void		free_manager(void);

// tracker.c

void		add_deallocator(void *ptr, void (*fct)(void *));
void		init_tracker(void);

//			INIT			//

/// init_shell.c

void		init_shell(char **env);

//			INTERPRETER		//

/// interpreter.c

t_list		*interpreter(t_list *tokens, char **env);

/// interpreter_utils.c

void		free_command(t_command *cmd_data);
size_t		get_word_count(t_list *tokens);
char		**get_arg_array(t_list *tokens);
char		*find_cmd_path(const char *cmd_name);

//			LEXER			//

///  QUOTES  ///

//// are_quotes_closed.c

bool		are_quotes_closed(const char *str);

///  TOKENS  ///

//// lexer.c

t_list		*lexer_root(const char *str);
t_list		*lexer(const char *str);

//// assign_states_utils.c

void		update_state_assign(const char c, t_qstate *state);
bool		is_assign(const char *word);

//// assign_states.c

bool		start_state_assign(const char **word, t_qstate *state);
bool		word_state_assign(const char **word, t_qstate *state);
bool		squote_state_assign(const char **word, t_qstate *state);
bool		dquote_state_assign(const char **word, t_qstate *state);

//// token_utils.c

t_token		*init_token(t_toktype type, char *value);
t_toktype	get_type_from_tok(t_token *tok);
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
				const char *spec_tok[]);

//// word_utils.c

bool		is_separator(const char c);
void		update_state(t_qmachine *const machine);
void		init_qmachine(t_qmachine *const machine, const char *str);
void		quote_state(t_qmachine *const machine, const char quote);

//			PARSER			//

/// parser.c

bool		parser(t_list *tokens);

/// parser_utils.c

void		print_pars_error(t_token *token);

//			PRINT			//

/// test_print.c

void		print_command(t_list *token_lst);
void		print_strs(char **strs);
void		print_cmd(t_list *cmds);

/// print_errror.c

void		print_error(const char *format, ...);

//			PROMPT			//

/// prompt.c

void		prompt(void);

//			SIGNAL			//

/// signal.c

void		set_catcher(void);

#endif
