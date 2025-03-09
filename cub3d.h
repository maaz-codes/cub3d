#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>

// MLX
#define screenWidth 1280
#define screenHeight 1080
#define mapWidth 10
#define mapHeight 5

// COLORS
#define COLOR_WHITE   0xFFFFFF
#define COLOR_RED     0x00FF0000  // (255, 0, 0)
#define COLOR_GREEN   0x0000FF00  // (0, 255, 0)
#define COLOR_BLUE    0x000000FF  // (0, 0, 255)
#define COLOR_YELLOW  0x00FFFF00  // (255, 255, 0)
#define COLOR_PURPLE 0x800080
#define COLOR_MAGENTA 0xFF00FF

// KEYS
# define KEY_W 13     
# define KEY_A 0     
# define KEY_S 1     
# define KEY_D 2     
# define KEY_LEFT 123
# define KEY_RIGHT 124

// GENERAL
# define TRUE 1
# define FALSE 0
# define WALKABLE 0
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.2


typedef struct 	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_tex
{
	t_img	img;
	int		ht;
	int		wd;
}				t_tex;

typedef struct  s_cub
{
    void			*connection;
	void			*win;
	t_img			img;
	int 			(*map)[mapWidth];
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
	double			drawStart;
	double			drawEnd;
	double			lineHeight;
	t_tex			*north;
	t_tex			*south;
	t_tex			*east;
	t_tex			*west;
	int				ceil;
	int				floor;
	int				direc;
	int				map_ht;
	int				map_wd;
}               t_cub;

// main.c
int 			cub_rendering(t_cub *cub);
int				handle_key_event(int keycode, t_cub *cub);

// draw_utils.c
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			color_pxl(int x, int y, int color, t_cub *cub);
void 			draw_strip(int x, int start, int end, t_cub *cub);
// int 			get_color(t_cub *cub);
void			get_drawing_coords(t_cub *cub);

// motion.c
int				handle_keypress(int keycode, t_cub *cub);
void			cub_motion(double move_x, double move_y, t_cub *cub);

// ray_casting.c
void 			perform_dda(t_cub *cub);
void 			init_rays(int x, t_cub *cub);
void 			perform_ray_casting(int x, t_cub *cub);

// textures.c
t_tex 			*get_texture(char *path, t_cub *cub);
void 			draw_tex(int x, int start, int end, t_cub *cub);
int 			get_texture_pixel(t_cub *cub, int x, int y);

// game_utils.c
void 			print_map(char **map);
unsigned long 	getTicks(t_cub *cub);


#endif