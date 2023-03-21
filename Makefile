###############
#### SHELL ####
###############

SHELL		= /usr/bin/bash

##############
#### SRCS ####
##############

PATH_SRCS	+=	srcs/
SRCS	 	+=	main.c

vpath %.c $(PATH_SRCS)

##############
#### OBJS ####
##############

PATH_OBJS	+=	objs/
OBJS		+=	$(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

#####################
#### COMPILATION ####
#####################

CC			=	gcc
CFLAGS		+=	-Wall
CFLAGS		+=	-Werror
CFLAGS		+=	-Wextra

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

all 	:	$(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $< -o $@
	$(ECHOC) $(GREEN) "\n--> $(NAME) COMPILED !"$(NC)"\n\n"

$(OBJS) :	$(PATH_OBJS)/%.o: %.c Makefile
	$(ECHO) $(ORANGE) "Compiling $<"
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	$(RM) -r $(PATH_OBJS)
	$(ECHOC) $(GREEN) "--> .o files deleted !"$(NC)"\n"

fclean	:	clean
	$(ECHOC) $(YELLOW) "Cleaning up $(NAME)..." $(NC)
	$(RM) $(NAME)
	$(ECHOC) $(GREEN) "--> $(NAME) deleted !"$(NC)"\n"

re 		: fclean
	echo -e $(YELLOW) "\nRebuilding..." $(NC)
	$(MAKE) -s

.PHONY	: all clean fclean re start
.SILENT	: all clean fclean re $(NAME) $(OBJS)
