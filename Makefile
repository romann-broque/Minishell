PATH_SRCS	+=	srcs/
SRCS	 	+=	main.c

vpath %.c $(PATH_SRCS)

PATH_OBJS	+=	objs/
OBJS		+=	$(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

CC			=	gcc
CFLAGS		+=	-Wall
CFLAGS		+=	-Werror
CFLAGS		+=	-Wextra
NAME		+=	minishell

all 	:	$(NAME)

$(NAME) :	$(OBJS) $(MAIN_OBJS)
		echo $(SRCS)
		$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJS) -o $(NAME)

$(OBJS) :	$(PATH_OBJS)/%.o: %.c
		mkdir -p $(PATH_OBJS)
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		$(RM) -r $(PATH_OBJS)

fclean	:	clean
		$(RM) $(NAME)

re 		: fclean all

.PHONY	: all clean fclean re
