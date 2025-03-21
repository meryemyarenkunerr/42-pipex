NAME	= pipex

SRCS	= srcs/pipex.c srcs/utils.c
OBJS	= ${SRCS:.c=.o}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS}
	make -C ./libft
	${CC} ${OBJS} -Llibft -lft -o ${NAME}

clean:
	make clean -C ./libft
	rm -f ${OBJS}

fclean:		clean
	make fclean -C ./libft
	rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re