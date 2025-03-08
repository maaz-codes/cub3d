#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1000

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>

// MLX
#define screenWidth 1280
#define screenHeight 1024
#define mapWidth 24
#define mapHeight 24

// COLORS
#define COLOR_WHITE   0xFFFFFF
#define COLOR_RED     0x00FF0000  // (255, 0, 0)
#define COLOR_GREEN   0x0000FF00  // (0, 255, 0)
#define COLOR_BLUE    0x000000FF  // (0, 0, 255)
#define COLOR_YELLOW  0x00FFFF00  // (255, 255, 0)
#define COLOR_PURPLE 0x800080
#define COLOR_MAGENTA 0xFF00FF

// KEYS
// # define KEY_LEFT 123
// # define KEY_RIGHT 124
// # define KEY_UP 126
// # define KEY_DOWN 125
// # define KEY_PLUS 24      
// # define KEY_MINUS 27     

# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_PLUS 14      
# define KEY_MINUS 12   

// GENERAL
# define TRUE 1
# define FALSE 0

# define WALKABLE 48
// # define WALKABLE 0
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.2


typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct  s_cub
{
    void			*connection;
	void			*win;
	t_img			img;
	// int 			(*map)[mapHeight];
	char			**map;
	struct timeval 	start_time;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	int				mapX;
	int				mapY;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int				stepX;
	int				stepY;
	int				side;
	int				color;
	double			drawStart;
	double			drawEnd;
	double			lineHeight;
}               t_cub;

// get next line
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

//parse struct
typedef struct parsing
{	
	int				row;
	int				map_length;
	char			**file_data;
	char			**map;
	int				**check_valid;
	char			**textures;
	int				**rgb;
	char			player;
	int				x_pos;
	int				y_pos;
}	t_parsing;

//libft 
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlen(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strtrim(char const *s1, char const *set);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				ft_bzero(void *s, size_t n);
char				*ft_strchr(const char *s, int c);
int					ft_atoi(const char *nptr);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s1);


// get_next_line.c
char				*get_next_line(int fd);
t_list				*ft_lstlast(t_list *lst);
void				ft_append(t_list **list, char *buf);
int					lentillnewline(t_list *list);
int					found_newline(t_list *list);
void				copy_str(t_list *list, char *str);
void				clean_node(t_list **list, int len, int i);
char				*get_theline(t_list *list);
void				ft_lstclear(t_list **lst);

//freeing
void 				free_double(char **str, int size);
void 				free_int(int **num, int size);
void 				free_data(t_parsing *parse);

//parsing
int					parse_init_save(t_parsing **parse, char **av);
int 				init_textures_and_rgb(t_parsing **parse);
int 				init_parse_struct(t_parsing **parse, char **av);
int 				init_file_data(t_parsing *parse);
void 				get_rows(t_parsing *parse, int file);
int 				get_file_data(t_parsing *parse, int file);
int 				file_open(char *av);
int 				check_which_texture(char *file_check, int i);
void 				check_valid_values(char *file_check, int i, t_parsing *parse, char *mode);
int 				save_texture(t_parsing *parse, int file);
int					rgb_save(t_parsing *parse);
int 				check_txt(t_parsing *parse, int *valid, int row, int i);
int 				rgb_check(t_parsing *parse, int *valid);
int 				is_valid(t_parsing *parse);
// void 				print_validity(int texture, int rgb, t_parsing *parse);
void 				print_rgb_map(t_parsing *parse);
void				get_player_modif_map(t_parsing *parse);
void				print_info(t_parsing *parse, char **av);
void				print_rgb_map(t_parsing *parse);

//parsing map
int 				get_map(t_parsing *parse);
int 				parse_map(t_parsing *parse);
int 				checkpoint(char **map, int row, int i);
int 				last_row(t_parsing *parse);
int 				check_top_down(char **map,int last_row);
int 				check_bottom(t_parsing *parse);
int 				one_player(t_parsing *parse);
int 				check_direction(char player);
int 				one_check(char **map, int row, int i);
int 				only_spaces(char *map);
int 				player_zero_check(char **map, int row, int i);
int 				valid_nsew(char **map, int row, int i);

// main.c
int 				cub_rendering(t_cub *cub);
int					handle_key_release(int keycode, t_cub *cub);

// draw_utils.c
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				color_pxl(int x, int y, int color, t_cub *cub);
void 				draw_strip(int x, int start, int end, int color, t_cub *cub);

// motion.c
int					handle_key_release(int keycode, t_cub *cub);
void				cub_motion(double move_x, double move_y, t_cub *cub);

#endif