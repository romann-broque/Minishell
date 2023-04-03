/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 14:10:16 by mat              ###   ########.fr       */
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
# define S_QUOTE		'\''
# define D_QUOTE		'\"'
# define SPEC_VAR_LEN	2
# define LAST_RETVAL	EXIT_SUCCESS

//////////////////
/// STRUCTURES ///
//////////////////

typedef enum e_var_state
{
	E_STD,
	E_DOUBLE_QUOTE,
	E_SINGLE_QUOTE,
	E_DOLLAR,
	E_EOF
}				t_vstate;

typedef struct s_vmachine
{
	t_vstate	state;
	t_vstate	prev_state;
	size_t		word_len;
	size_t		i;
	char		*line;
}			t_vmachine;

/////////////////
/// FUNCTIONS ///
/////////////////

// exit_shell

void	exit_shell(const int exit_value);

// prompt

void	prompt(void);

// var

char	*expand_var(char *line);
void	std_state(t_vmachine *const machine);
void	d_quote_state(t_vmachine *const machine);
void	s_quote_state(t_vmachine *const machine);
void	var_state(t_vmachine *const machine);
bool	is_in_var_charset(char c);
bool	is_special_var(char c);
void	handle_var_start(t_vmachine *const machine);
void	translate_var(t_vmachine *const machine);
void	change_state(t_vstate new_state, t_vmachine *const machine);
char	*replace_and_free(
			char *src,
			char *replace,
			size_t index,
			size_t delete_len
			);

// signal

void	set_catcher(void);

// print

void	print_command(char **const command);

#endif
