NAME = cub3d

# SRC = fractol.c maths.c mlx_utils.c rendering.c events.c libft.c errors.c \
# 		mandelbrot.c julia.c 

SRC = 	cub3d.c \
		draw_utils.c \
		motion.c \
		ray_casting.c \

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
