NAME = cub3d

		
SRC = 	test.c \
			parsing/parse.c \
			parsing/parse_utils.c \
			parsing/texture_parse.c \
			parsing/rgb_parse.c \
			parsing/save_texture.c \
			parsing/save_rgb.c \
			parsing/free_data.c \
			parsing/get_map.c \
			parsing/get_file_data.c \
			parsing/parse_map.c \
			parsing/parse_map_utils.c \
			parsing/parse_utils_two.c \
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
					libft/ft_strdup.c \

OBJ = $(SRC:.c=.o)

CC = cc -g3
# CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compiling..."
	#@$(MAKE) all -C mlx
	#$(MLX_FLAGS)
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
