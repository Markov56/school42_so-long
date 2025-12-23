NAME = so_long

SRC = main.c \
		utils.c \
		map_parser.c \
		map_validator.c \
		render.c \
		free_exit.c \
		keypress_handler.c

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
# TODO
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include

LIBFT_PATH = ./libs/libft
LIBFT = -L ${LIBFT_PATH} -lft

MLX_PATH = ./libs/mlx
MLX = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${NAME}: ${OBJS}
	${MAKE} -C ${LIBFT_PATH} all
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} ${LIBFT} ${MLX} -o ${NAME}

all: ${NAME}

clean:
	${MAKE} -C ${LIBFT_PATH} clean
	${RM} ${OBJS}

fclean: clean
	${MAKE} -C ${LIBFT_PATH} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
