NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./src/printf -lftprintf -L./src/libft -lft -L./mlx42 -lmlx -lXext -lX11 -lm -Iinclude -ldl -lglfw -lGL -lGLU

SRC = main.c process_map_file.c map_utils.c map_utils_2.c mlx_process.c player_move.c graphic_funcs.c graphic_funcs_2.c do_moves.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./src/libft
	$(MAKE) -C ./src/printf
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

clean:
	$(MAKE) -C ./src/libft clean
	$(MAKE) -C ./src/printf clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C ./src/libft fclean
	$(MAKE) -C ./src/printf fclean
	rm -f $(NAME)

re: fclean all
