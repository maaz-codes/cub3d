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
# define WALKABLE 0


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
	int 			(*map)[mapHeight];
	struct timeval 	start_time;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double 			move_speed;
	double 			rot_speed;
}               t_cub;

// main.c
int cub_rendering(t_cub *cub);
int	handle_key_release(int keycode, t_cub *cub);

#endif