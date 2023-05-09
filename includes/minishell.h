/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:24 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/09 16:05:18 by rbroque          ###   ########.fr       */
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
# include <unistd.h>
# include <fcntl.h>

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
# define ECHO_OPT		"-n"
# define BACKPATH		"/.."
# define NEWLINE_STR	"\n"
# define SPACE_STR		" "
# define DQUOTE_STR		"\""
# define SHLVL_DEFAULT	"0"

// builtins

# define CD_BUILTIN		"cd"
# define ECHO_BUILTIN	"echo"
# define EXIT_BUILTIN	"exit"
# define EXPORT_BUILTIN	"export"
# define PWD_BUILTIN	"pwd"
# define UNSET_BUILTIN	"unset"
# define ENV_BUILTIN	"env"

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
# define SHLVL_VAR		"SHLVL"

// tok_string

# define LCHEVRON			"<"
# define RCHEVRON			">"
# define DOUBLE_LCHEVRON	"<<"
# define DOUBLE_RCHEVRON	">>"
# define PIPE				"|"
# define OR					"||"
# define AND				"&&"
# define ASSIGN_EQ			"="
# define SEP				" "
# define END_STR			"newline"

// error string

# define SYNTAX_ERROR			"syntax error near unclosed quote"
# define MALLOC_ERROR			"Malloc error"
# define PARS_ERROR				"syntax error near unexpected token"
# define CNF					"command not found"
# define IS_DIR					"Is a directory"
# define STAT_ERROR				"Failed to stat file"
# define TOO_MANY_ARGS			"too many arguments"
# define ERROR_ACCESS_DIR		"error retrieving current directory"
# define ERROR_ACCESS_PAR_DIR	"cannot access parent directories"
# define NUM_ARG_REQ			"numeric argument required"
# define INVALID_ID				"not a valid identifier"
# define NO_SUCH_FILE			"No such file or directory"

// char types

# define TOK_LEXEME		"<>|&="
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

# define NEXT_TOK_MAX	13
# define NB_DEALLOCATOR	5
# define CD_EXP_ARG		2

// return value

# define NO_ACCESS		126
# define NO_FILE		127
# define INCORRECT_USE	2
# define IGNORE_TOK		1
# define LAST_RETVAL	EXIT_SUCCESS

// enum

# define ASSIGN_START	0

// var_flag

# define SLEEP_MASK		0x00
# define SET_MASK		0x0f
# define EXPORT_MASK	0xf0
# define ENV_MASK		0xff

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
	T_SEPARATOR,
	T_ASSIGN,
	T_GENERIC,
	T_QGENERIC,
	T_START,
	T_END,
	T_INVALID,
}			t_toktype;

typedef enum e_toktype_short
{
	T_LCH,
	T_RCH,
	T_DLCH,
	T_DRCH,
	T_P,
	T_O,
	T_A,
	T_SEP,
	T_ASN,
	T_G,
	T_QG,
	T_ST,
	T_ED,
	T_IVD,
}			t_toktype_short;

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
	t_toktype		curr;
	t_toktype_short	next[NEXT_TOK_MAX];
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

typedef struct s_builtin_mapper
{
	const char	*name;
	int			(*fct)(t_command *cmd_data);
}				t_builtin_mapper;

typedef struct s_var
{
	char	*key;
	char	*value;
	uint8_t	flags;
}				t_var;

typedef struct s_global
{
	int		last_ret_val;
	t_list	*garbage;
	t_list	*env;
	bool	is_stoppable;
	int		stdin;
	int		stdout;
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

t_var		*get_var_from_env(const char *key, t_list *env);
void		change_var(const char *key, const char *value,
				uint8_t flags, t_list **env);
void		update_var(const char *key, const char *value, const uint8_t flags);

//// dup_env_lst_to_array.c

char		**get_env_array(t_list *env_lst, const uint8_t mask,
				char *(*assign_fct)(t_var *));

/// env_utils.c

t_var		*init_var(const char *name, const char *value, uint8_t flags);
t_var		*dup_var(t_var *var);
t_var		*get_var(const char *var_name);
void		set_var_flag(const char *key, const uint8_t flags);
void		free_var(t_var *var);

/// export_utils.c

void		add_assignation_to_env(char *arg);
void		add_key_to_env(char	*arg);
void		sort_strings(char *strings[]);
t_var		*export_var_from_str(char *str, bool is_only_key);

/// ft_getenv.c

char		*ft_getenv_local(const char *var_name, char **env);
char		*ft_getenv(const char *var_name);

/// init_env.c

t_var		*init_var_from_str(const char *str);
void		init_env(t_global *global, char **env);

///			PATH				///

//// clean_path.c

void		clean_path(char **path);

//// get_path.c

bool		is_cmd_path(t_command *cmd);
char		*get_cmd_path(t_command *cmd_data);
char		*get_path_from_env(const char *suffix,
				const char *pathvar_name, char **env);

//// path_access.c

bool		is_cmd_accessible(const char *path);

//// cmd_path_utils.c

char		*dup_path_from_cmd(t_command *cmd);
void		add_fwd_slash(char **paths);
bool		is_var_path_in_env(char **env, const char *pathvar_name);
bool		is_empty_str(const char *str);
bool		is_path_var(const char *env_line, const char *pathvar_name);

//			EXECUTION			//

/// execution.c

void		execution(t_command *command);

/// exec_binary.c

void		exec_binary(t_command *cmd_data, char *path);

///  BUILTIN  ///

/// dup_export_lst_to_array.c

char		**dup_export_lst_to_array(t_list *env_lst);

//// exec_buitlin.c

void		exec_builtin(t_command *command);

//// is_builtin.c

bool		is_builtin(t_command *cmd_data);

////  BUILTIN_FCTS  ////

///// cd.c

int			cd_builtin(t_command *cmd_data);

///// echo.c

int			echo_builtin(t_command	*cmd_data);

///// env.c

int			env_builtin(t_command *cmd_data);

///// exit.c

int			exit_builtin(t_command *cmd_data);

///// export.c

int			export_builtin(t_command *cmd_data);

///// pwd.c

int			pwd_builtin(__attribute__((unused)) t_command *cmd_data);

///// unset.c

int			unset_builtin(t_command *cmd);

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

void		exit_shell(const int exit_value, const bool is_print);

/// exit_utils.c

int			extract_return_status(int status);
void		update_error_val(int error_nbr);

//			EXPANSION			//

//// is_assign_tok.c

bool		is_assign_tok_state(const char *str);
bool		is_assign_tok(t_token *token);

/// expand_command.c

void		expand_command(t_list **tokens);

/// expand_utils.c

void		remove_sep_tok(t_list **tokens);

/// merge_gen.c

void		merge_gen_lst(t_list *tokens);

/// split_gen.c

void		split_gen(t_list **tokens);

/// update_tok_type.c

void		set_qgen_to_gen(t_token *tok);
void		set_assign_tok(t_token *tok);
void		set_simple_eq_to_gen(t_token *tok);

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

t_list		*interpreter(t_list *tokens, t_list *env);

/// interpreter_utils.c

bool		is_assign_mode(t_list *tokens);

/// cmd_mode.c

t_list		*cmd_mode(t_list *tokens, t_list *env);

///			COMMAND			///

//// command_utils.c

char		**dup_env_lst_to_array(t_list *env_lst);
t_command	*init_command(t_list *tokens, t_list *env);
void		free_command(t_command *cmd_data);

////////////

//// get_arg_array.c

void		append_to_arg_array(t_command *cmd, t_list *tokens);
char		**get_arg_array(t_list *tokens);

//// redirection.c

void		update_fds(t_toktype toktype, t_token *tok, t_command *cmd);

//			LEXER			//

///  QUOTES  ///

//// are_quotes_closed.c

bool		are_quotes_closed(const char *str);

///  TOKENS  ///

//// lexer.c

t_list		*lexer_root(const char *str);
t_list		*lexer(const char *str);

//// token_utils.c

t_token		*init_token(t_toktype type, char *value);
t_toktype	get_type_from_tok(t_token *tok);
char		*get_str_from_tok(t_token *tok);
void		free_token(t_token *tok);

//// tokenizer_utils.c

bool		is_assign(const char *word);
bool		is_qword(const char *word);

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
