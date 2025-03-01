NAME = cub3d

# SRC = fractol.c maths.c mlx_utils.c rendering.c events.c libft.c errors.c \
		mandelbrot.c julia.c 

# cub3d.c \

SRC =   parsing/parse.c \
		parsing/texture_parse.c \
		parsing/rgb_parse.c \
		parsing/save_texture.c \
		parsing/save_rgb.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
			libft/ft_strncmp.c \
			libft/ft_strlen.c \
			libft/ft_strlcpy.c \
			libft/ft_calloc.c \
			libft/ft_strtrim.c \
			libft/ft_bzero.c \
			libft/ft_strchr.c \
			libft/ft_atoi.c \
			libft/ft_split.c \

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compiling..."
	# @$(MAKE) all -C mlx
	# $(MLX_FLAGS)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
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
