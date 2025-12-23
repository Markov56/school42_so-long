NAME = so_long

SRC = main.c utils.c map_parser.c map_validator.c

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
# TODO
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
INCLUDE = -I include
LIBFT_PATH = ./libft
LIBFT = -L ${LIBFT_PATH} -lft

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${MAKE} -C ${LIBFT_PATH} all
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} ${LIBFT} -o ${NAME}

all: ${NAME}

clean:
	${MAKE} -C ${LIBFT_PATH} clean
	${RM} ${OBJS}

fclean: clean
	${MAKE} -C ${LIBFT_PATH} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
