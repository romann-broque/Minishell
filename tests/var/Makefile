##############
#### NAME ####
##############

NAME		+=	print_var

##############
#### SRCS ####
##############

PATH_SRCS	+= ./

### tests/

SRCS		+= var.c

vpath %.c $(PATH_SRCS)

##############
#### OBJS ####
##############

PATH_OBJS	+=	objs/
OBJS		+=	$(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

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

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT) $(LINKS)

$(OBJS) :	$(PATH_OBJS)/%.o: %.c Makefile $(HEADERS)
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean	:
	$(RM) -r $(PATH_OBJS)

fclean	:	clean
	$(RM) $(NAME)

re 		: fclean
	$(MAKE) -s

.PHONY	: all clean fclean re
.SILENT	:
