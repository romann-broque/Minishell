###############
#### SHELL ####
###############

SHELL		= /usr/bin/bash

##############
#### SRCS ####
##############

PATH_SRCS	+=	srcs/
PATH_SRCS	+=	srcs/batch/
PATH_SRCS	+=	srcs/env/
PATH_SRCS	+=	srcs/env/path/
PATH_SRCS	+=	srcs/execution/
PATH_SRCS	+=	srcs/execution/builtin/
PATH_SRCS	+=	srcs/execution/builtin/builtin_fcts/
PATH_SRCS	+=	srcs/execution/builtin/cwd/
PATH_SRCS	+=	srcs/execution/builtin/cwd/clean_path/
PATH_SRCS	+=	srcs/exit/
PATH_SRCS	+=	srcs/expansion/
PATH_SRCS	+=	srcs/free/
PATH_SRCS	+=	srcs/init/
PATH_SRCS	+=	srcs/interpreter/
PATH_SRCS	+=	srcs/expansion/var/
PATH_SRCS	+=	srcs/lexer/
PATH_SRCS	+=	srcs/lexer/quotes/
PATH_SRCS	+=	srcs/lexer/tokens/
PATH_SRCS	+=	srcs/lexer/word/
PATH_SRCS	+=	srcs/parser/
PATH_SRCS	+=	srcs/print/
PATH_SRCS	+=	srcs/prompt/
PATH_SRCS	+=	srcs/signal/

### srcs/

SRCS	 	+=	minishell.c

### srcs/

SRCS		+=	batch.c

### srcs/env/

SRCS		+= change_var.c
SRCS		+= ft_getenv.c
SRCS		+= init_env.c

### srcs/env/path/

SRCS		+=	clean_path.c
SRCS		+=	get_path.c
SRCS		+=	cmd_path_utils.c

### srcs/execution/

SRCS	 	+=	execution.c

### srcs/execution/builtin/

SRCS	 	+=	exec_builtin.c
SRCS	 	+=	is_builtin.c

### srcs/execution/builtin/builtin_fcts/

SRCS	 	+=	exit.c
SRCS		+=	cd.c
SRCS		+=	pwd.c

### srcs/execution/builtin/cwd/

SRCS	 	+=	cd_arg.c
SRCS	 	+=	cd_utils.c
SRCS	 	+=	cwd_utils.c

### srcs/execution/builtin/cwd/clean_path

SRCS		+=	clean_pwd.c
SRCS		+=	ft_realpath_utils.c
SRCS	 	+=	ft_realpath.c

### srcs/exit/

SRCS	 	+=	exit_shell.c

### srcs/expansion/

SRCS	 	+=	expand_command.c

### srcs/expansion/var/

SRCS		+=	handle_var.c
SRCS		+=	var_machine.c
SRCS		+=	var_state_func.c
SRCS		+=	var_utils.c

### srcs/free/

SRCS		+=	free_manager.c
SRCS		+=	tracker.c

### srcs/init/

SRCS		+=	init_shell.c

### srcs/interpreter/

SRCS		+=	interpreter.c
SRCS		+=	interpreter_utils.c

### srcs/lexer/

### srcs/lexer/quotes/

SRCS		+=	are_quotes_closed.c

### srcs/lexer/tokens/

SRCS		+=	assign_states_utils.c
SRCS		+=	assign_states.c
SRCS		+=	lexer.c
SRCS		+=	token_utils.c
SRCS		+=	tokenizer.c

### srcs/lexer/word/

SRCS		+=	get_words.c
SRCS		+=	parse_states.c
SRCS		+=	strs_to_lst.c
SRCS		+=	word_utils.c

### srcs/parser/

SRCS		+=	parser.c
SRCS		+=	parser_error.c

### srcs/print/

SRCS		+=	test_print.c
SRCS		+=	print_error.c

### srcs/prompt/

SRCS	 	+=	prompt.c

### srcs/signal/

SRCS		+=	signal.c

vpath %.c $(PATH_SRCS)

##############
#### OBJS ####
##############

PATH_OBJS	+=	objs/
OBJS		+=	$(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

##################
#### INCLUDES ####
##################

INCLUDES	+=	-I includes/
INCLUDES	+=	-I $(LIBFT_FOLDER)/includes

#################
#### HEADERS ####
#################

PATH_HEADERS +=	includes/

HEADERS		+=	minishell.h

vpath %.h $(PATH_HEADERS)

###############
#### LIBFT ####
###############

LIBFT_FOLDER =	libft/
LIBFT		 =	$(LIBFT_FOLDER)/libft.a

###############
#### LINKS ####
###############

LINKS += -lreadline

################
#### TESTER ####
################

TESTER_FOLDER	= ./tests/
ENV_FOLDER		= $(TESTER_FOLDER)/env/
ENV				= $(TESTER_FOLDER)/env/env.sh

### MIN

MINTEST_FOLDER	= $(TESTER_FOLDER)/tester_folder/
TESTER			= $(MINTEST_FOLDER)/tester.sh

### CUNIT

CUNIT_FOLDER	= $(TESTER_FOLDER)/CUNIT/
CUNIT			= $(CUNIT_FOLDER)/run_cunit.sh

### VALGRIND

CURR_FOLDER_VALGRIND = ./tests/valgrind/
SUPPRESSION_FILE	= $(CURR_FOLDER_VALGRIND)suppressions.supp

ifeq ($(valgrind), true)
	VALGRIND	+= valgrind
endif

#####################
#### COMPILATION ####
#####################

CC			=	cc

CFLAGS		+=	-Wall
CFLAGS		+=	-Wextra

ifneq ($(no_error), true)
	CFLAGS		+=	-Werror
endif

ifneq ($(no_error), true)
	CFLAGS		+=	-Werror
endif

ifeq ($(debug), true)
	CFLAGS	+= -fsanitize=address,undefined -g3
endif

##############
#### NAME ####
##############

NAME		+=	minishell

#################
#### DISPLAY ####
#################

RED='\033[0;31m'
GREEN='\033[1;32m'
ORANGE='\033[0;33m'
YELLOW='\033[1;33m'
BLUE='\033[1;36m'
NC='\033[0m' # No Color

ifndef ECHO
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)

ECHOC = echo -ne "\r\033[2K"
ECHO = $(ECHOC) $(ORANGE) "[`expr $C '*' 100 / $T`%]"
endif

###############
#### RULES ####
###############

all 	:	$(LIBFT) $(NAME)

$(LIBFT):
	echo -e $(BLUE) "\n====> Building libft.a <===="$(NC)"\n"
	$(MAKE) -sC $(LIBFT_FOLDER)
	echo -e $(BLUE) "\n====> Building $(NAME) <===="$(NC)"\n"

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT) $(LINKS)
	$(ECHOC) $(GREEN) "--> $(NAME) COMPILED !"$(NC)"\n\n"

$(OBJS) :	$(PATH_OBJS)/%.o: %.c Makefile $(HEADERS)
	$(ECHO) $(ORANGE) "Compiling $<"
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

test	:
	$(MAKE) re -s
	$(MAKE) -sC $(CUNIT_FOLDER)
	echo -e $(BLUE) "\n====> CUNIT TESTS"$(NC)"\n"
	source $(ENV); $(CUNIT) $(VALGRIND)
	echo -e $(BLUE) "\n====> MINISHELL TESTS"$(NC)"\n"
	$(TESTER) $(VALGRIND)

clean	:
	$(RM) -r $(PATH_OBJS)
	$(MAKE) -sC $(LIBFT_FOLDER) clean > /dev/null
	$(MAKE) -sC $(CUNIT_FOLDER) clean > /dev/null
	$(ECHOC) $(GREEN) "--> .o files deleted !"$(NC)"\n"

fclean	:	clean
	$(ECHOC) $(YELLOW) "Cleaning up $(NAME)..." $(NC)
	$(MAKE) -sC $(LIBFT_FOLDER) fclean > /dev/null
	$(MAKE) -sC $(CUNIT_FOLDER) fclean > /dev/null
	$(RM) $(NAME)
	$(ECHOC) $(GREEN) "--> $(NAME) deleted !"$(NC)"\n"

re 		: fclean
	echo -e $(YELLOW) "\nRebuilding..." $(NC)
	$(MAKE) -s

.PHONY	: all test clean fclean re
.SILENT	: all test clean fclean re $(NAME) $(OBJS) $(LIBFT)
