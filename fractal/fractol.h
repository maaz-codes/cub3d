/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:07:18 by maakhan           #+#    #+#             */
/*   Updated: 2024/09/29 11:01:11 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_HEIGHT 800
# define WIN_WIDTH 800

// #define ITERATIONS 				100
# define ESCAPE_VALUE 4

// colors
# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xFFFFFF

# define COLOR_BLUE_VIOLET 0x8A2BE2
# define COLOR_MAGENTA 0xFF00FF

# define COLOR_DARK_GREEN 0x006400
# define COLOR_BRIGHT_GREEN 0x00FF00

# define COLOR_PURPLE 0x800080
# define COLOR_ELECTRIC_PURPLE 0xBF00FF

// keys
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_PLUS 24      // color change
# define KEY_MINUS 27     // color change
# define KEY_SPACE_BAR 49 // pause animation
# define KEY_ESC 53       // exits
# define KEY_I 34         // iterations ++
# define KEY_O 31         // iterations --
# define KEY_P 35         // pause motion_track

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_fractal
{
	void	*connection;
	void	*win;
	char	*name;
	t_img	img;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		iterations;
	int		motion_flag;
}			t_fractal;

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

// maths
double		scale(double num, double new_min, double new_max);
t_complex	add_complex(t_complex a, t_complex b);
t_complex	square_complex(t_complex number);

// mlx_utils
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);

// rendering
void		fractal_rendering(t_fractal *fractal);
void		color_pxl(int x, int y, t_fractal *fractal);
int			color_themes(int i, t_fractal *fractal);

// events
int			handle_mouse_click(int keycode, int x, int y, t_fractal *fractal);
int			handle_key_release(int keycode, t_fractal *fractal);
int			handle_no_event(t_fractal *fractal);
int			handle_mouse_motion(int mouse_x, int mouse_y, t_fractal *fractal);
int			handle_closing(t_fractal *fractal);

// libft
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
double		ft_atof(const char *str);

// errors
int			fractal_menu(void);
int			check_complex(const char *str);
int			check_args(int ac, char **av, t_fractal *fractal);

// fractals
int			mandelbrot(t_fractal *fractal);
int			julia(char *num1, char *num2, t_fractal *fractal);
void		algo_mandelbrot(int x, int y, t_fractal *fractal);
void		algo_julia(int x, int y, t_fractal *fractal);

// main
void		reset_fractal(t_fractal *fractal);

#endif