NAME = cub3d

SRC = 	main.c \
		execution/draw_utils2.c \
		execution/motion2.c \
		execution/ray_casting2.c \
		execution/events.c \
		textures2.c \
		error.c \

OBJ = $(SRC:.c=.o)

CC = cc

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compiling..."
	@$(MAKE) all -C mlx
	@$(CC) $(MLX_FLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation finished: try: ./$(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@$(MAKE) clean -C mlx
	@rm -f $(OBJ)
	@echo "clean done!"

fclean: clean
	@$(MAKE) clean -C mlx
	@rm -f $(NAME)
	@echo "fclean done!"

re: fclean all

.PHONY: all clean fclean re
