/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:12 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/13 17:51:23 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define SCREENWIDTH 1280
# define SCREENHEIGHT 1080

// COLORS
# define COLOR_BLACK 	0x000000
# define COLOR_WHITE   	0xFFFFFF
# define COLOR_RED     	0x00FF0000  
# define COLOR_GREEN   	0x0000FF00 
# define COLOR_BLUE    	0x000000FF 
# define COLOR_YELLOW  	0x00FFFF00
# define COLOR_PURPLE 	0x800080
# define COLOR_MAGENTA 	0xFF00FF

// KEYS
# define KEY_W 13     
# define KEY_A 0     
# define KEY_S 1     
# define KEY_D 2     
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

// MLX_EVENTS
// MASK_KEY_UP 1L << 0
# define ON_KEY_UP 2
# define ON_DESTROY 17
# define MASK_KEY_UP 18
# define MASK_ON_DESTROY 6  

// GENERAL
# define TRUE 1
# define FALSE 0
# define WALKABLE '0'
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.2

// ERRORS
# define ERR_MALLOC 	4201
# define ERR_FILE 		4202
# define ERR_SYS_ARGS 	4203
# define ERR_MLX	 	4204

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_tex
{
	t_img	img;
	int		ht;
	int		wd;
}				t_tex;

typedef struct s_cub
{
	void			*connection;
	void			*win;
	t_img			img;
	char			**map;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	double			draw_start;
	double			draw_end;
	double			line_height;
	t_tex			*north;
	t_tex			*south;
	t_tex			*east;
	t_tex			*west;
	int				ceil;
	int				floor;
	int				direc;
	int				map_ht;
	int				map_wd;
	t_parsing		*parse;
}	t_cub;

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
char				*ft_strjoin(char const *s1, char const *s2);

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
void				free_double(char **str, int size);
void				free_int(int **num, int size);
void				free_data(t_parsing *parse);

//parsing
int					parse_init_save(t_parsing **parse, char **av);
int					init_textures_and_rgb(t_parsing **parse);
int					init_parse_struct(t_parsing **parse);
int					init_file_data(t_parsing *parse);
void				get_rows(t_parsing *parse, int file);
int					get_file_data(t_parsing *parse, int file);
int					file_open(char *av);
int					check_which_texture(char *file_check, int i);
void				check_valid_values(char *file_check, int i,
						t_parsing *parse, char *mode);
int					save_texture(t_parsing *parse, int file);
int					rgb_save(t_parsing *parse);
int					check_txt(t_parsing *parse, int *valid, int row, int i);
int					rgb_check(t_parsing *parse, int *valid);
int					is_valid(t_parsing *parse);
void				print_rgb_map(t_parsing *parse);
void				get_player_modif_map(t_parsing *parse);
void				print_rgb_map(t_parsing *parse);
int					valid_xpm_file(t_parsing *parse);
int					valid_cub_file(char *file_name);

//parsing map
int					get_map(t_parsing *parse);
int					parse_map(t_parsing *parse);
int					checkpoint(char **map, int row, int i);
int					last_row(t_parsing *parse);
int					check_top_down(char **map, int last_row);
int					check_bottom(t_parsing *parse);
int					one_player(t_parsing *parse);
int					check_direction(char player);
int					one_check(char **map, int row, int i);
int					only_spaces(char *map);
int					player_zero_check(char **map, int row, int i);
int					valid_nsew(char **map, int row, int i);

// main.c
void				cub_spawner(t_cub *cub);
void				cub_init(t_cub *cub, t_parsing **parse);
int					cub_rendering(t_cub *cub);
int					handle_key_event(int keycode, t_cub *cub);

// draw_utils.c
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				color_pxl(int x, int y, int color, t_cub *cub);
void				draw_strip(int x, int start, int end, t_cub *cub);
void				get_drawing_coords(t_cub *cub);

// motion.c
void				cub_motion(double move_x, double move_y, t_cub *cub);
void				rotation(int dir, t_cub *cub);
void				motion(double *mx, double *my, int dir, t_cub *cub);

// events.c
int					handle_key_event(int keycode, t_cub *cub);
int					handle_closing(t_cub *cub);

// ray_casting.c
void				perform_dda(t_cub *cub, t_parsing *parse);
void				init_rays(int x, t_cub *cub);
void				perform_ray_casting(int x, t_cub *cub);
void				init_direction(t_cub *cub, int direc);

// textures.c
void				init_textures(t_cub *cub, t_parsing *parse);
t_tex				*get_texture(char *path, t_cub *cub);
t_tex				*current_texture(t_cub *cub);
void				draw_tex(int x, int start, int end, t_cub *cub);
int					get_texture_pixel(t_cub *cub, int x, int y);

// errors.c
void				cub_slayer(t_cub *cub);
void				free_textures(t_cub *cub);
int					error_msg(int flag);

#endif