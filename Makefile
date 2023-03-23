###############
#### SHELL ####
###############

SHELL		= /usr/bin/bash

##############
#### SRCS ####
##############

PATH_SRCS	+=	srcs/
PATH_SRCS	+=	srcs/exit/
PATH_SRCS	+=	srcs/prompt/
PATH_SRCS	+=	srcs/signal/

### srcs/

SRCS	 	+=	minishell.c

### srcs/prompt/

SRCS	 	+=	prompt.c

### srcs/signal/

SRCS		+=	signal.c

### srcs/exit/

SRCS	 	+=	exit_shell.c

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

#####################
#### COMPILATION ####
#####################

CC			=	gcc
CFLAGS		+=	-Wall
CFLAGS		+=	-Werror
CFLAGS		+=	-Wextra

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

clean	:
	$(RM) -r $(PATH_OBJS)
	$(MAKE) -sC $(LIBFT_FOLDER) clean > /dev/null
	$(ECHOC) $(GREEN) "--> .o files deleted !"$(NC)"\n"

fclean	:	clean
	$(ECHOC) $(YELLOW) "Cleaning up $(NAME)..." $(NC)
	$(MAKE) -sC $(LIBFT_FOLDER) fclean > /dev/null
	$(RM) $(NAME)
	$(ECHOC) $(GREEN) "--> $(NAME) deleted !"$(NC)"\n"

re 		: fclean
	echo -e $(YELLOW) "\nRebuilding..." $(NC)
	$(MAKE) -s

.PHONY	: all clean fclean re
.SILENT	: all clean fclean re $(NAME) $(OBJS) $(LIBFT)
