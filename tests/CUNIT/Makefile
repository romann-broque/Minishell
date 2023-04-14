
###############
#### SHELL ####
###############

SHELL		= /usr/bin/bash

##############
#### SRCS ####
##############

PATH_SRCS	+=	srcs/
PATH_SRCS	+=	srcs/tests/
PATH_SRCS	+=	srcs/utils/

### srcs/

SRCS	 	+=	minishell.test.c

### srcs/tests/

SRCS	 	+=	are_quotes_closed.test.c
SRCS		+=	expand.test.c
SRCS	 	+=	get_words.test.c
SRCS	 	+=	interpreter.test.c
SRCS		+=	lexer_root.test.c
SRCS		+=	parser.test.c

### srcs/utils/

SRCS	 	+=	test_utils.test.c
SRCS	 	+=	list_test.test.c

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
INCLUDES	+=	-I ../../includes/
INCLUDES	+=	-I $(LIBFT_FOLDER)/includes

#################
#### HEADERS ####
#################

PATH_HEADERS +=	../../includes/
PATH_HEADERS +=	includes/

HEADERS		+=	minishell.h
HEADERS		+=	cunit.test.h

vpath %.h $(PATH_HEADERS)

###############
#### LIBFT ####
###############

LIBFT_FOLDER =	../../libft/
LIBFT		 =	$(LIBFT_FOLDER)/libft.a

#######################
#### MINISHELL_LIB ####
#######################

MIN_OBJS_ALL	=	$(wildcard ../../objs/*.o)
MIN_OBJS		:=	$(filter-out ../../objs/minishell.o,$(MIN_OBJS_ALL))
MINISHELL_LIB	=	libminishell.a

###############
#### LINKS ####
###############

LINKS += -lcunit

#####################
#### COMPILATION ####
#####################

CC			=	cc
CFLAGS		+=	-Wall
CFLAGS		+=	-Wextra

ifneq ($(no_error), true)
	CFLAGS		+=	-Werror
endif
ifeq ($(debug), true)
	CFLAGS	+= -fsanitize=address,undefined -g3
endif

##############
#### NAME ####
##############

NAME		+=	cunit

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

all 	:	$(MINISHELL_LIB) $(NAME)

$(MINISHELL_LIB): $(MIN_OBJS)
	ar rcs $@ $^
	$(ECHOC) $(GREEN) "--> $(MINISHELL_LIB) COMPILED !"$(NC)"\n"
	echo -e $(BLUE) "\n====> Building CUNIT TESTS <===="$(NC)"\n"

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT) $(LINKS) $(MINISHELL_LIB) $(LIBFT)
	$(ECHOC) $(GREEN) "--> $(NAME) COMPILED !"$(NC)"\n\n"

$(OBJS) :	$(PATH_OBJS)/%.o: %.c Makefile $(HEADERS)
	$(ECHO) $(ORANGE) "Compiling $<"
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean	:
	$(RM) -r $(PATH_OBJS)
	$(MAKE) -sC $(LIBFT_FOLDER) clean > /dev/null
	$(ECHOC) $(GREEN) "--> .o files deleted !"$(NC)"\n"

fclean	:	clean
	$(ECHOC) $(YELLOW) "Cleaning up $(NAME)..." $(NC)
	$(MAKE) -sC $(LIBFT_FOLDER) fclean > /dev/null
	$(RM) $(NAME)
	$(ECHOC) $(GREEN) "--> $(NAME) deleted !"$(NC)"\n"
	$(RM) $(MINISHELL_LIB)
	$(ECHOC) $(GREEN) "--> $(MINISHELL_LIB) deleted !"$(NC)"\n"

re 		: fclean
	echo -e $(YELLOW) "\nRebuilding..." $(NC)
	$(MAKE) -s

.PHONY	: all clean fclean re
.SILENT	: all clean fclean re $(NAME) $(OBJS) $(MINISHELL_LIB)
