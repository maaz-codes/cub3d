/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:28:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/08/31 15:25:13 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#include <math.h>

int	burning_ship(t_fractal *fractal)
{
	fractal->name = "burning_ship";
	fractal->julia_x = 0;
	fractal->julia_y = 0;
	return (1);
}

void	algo_burning_ship(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.x = (scale(x, -2, 2) * fractal->zoom) + fractal->shift_x;
	z.y = (scale(y, 2, -2) * fractal->zoom) + fractal->shift_y;
	c.x = z.x;
	c.y = z.y;
	i = 0;
	while (i < fractal->iterations)
	{
		z.x = fabs(z.x);
		z.y = (-1) * fabs(z.y);
		z = add_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > ESCAPE_VALUE)
		{
			color = color_themes(i, fractal);
			my_mlx_pixel_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_mlx_pixel_put(&fractal->img, x, y, COLOR_BLACK);
}

void	zoom_bonus(t_fractal *fractal, int mouse_x, int mouse_y, int flag)
{
	double	x;
	double	y;
	double	screen_x;
	double	screen_y;

	x = 0;
	y = 0;
	screen_x = 0;
	screen_y = 0;
	x = (scale(mouse_x, -2, 2) * fractal->zoom) + fractal->shift_x;
	y = (scale(mouse_y, 2, -2) * fractal->zoom) + fractal->shift_y;
	if (flag == 1)
		fractal->zoom /= 1.25;
	else if (flag == -1)
		fractal->zoom *= 1.25;
	screen_x = (scale(mouse_x, -2, 2) * fractal->zoom) + fractal->shift_x;
	screen_y = (scale(mouse_y, 2, -2) * fractal->zoom) + fractal->shift_y;
	fractal->shift_x += (x - screen_x);
	fractal->shift_y += (y - screen_y);
}

int	color_themes(int i, t_fractal *fractal)
{
	double	j;

	j = i;
	if (fractal->color_theme == 1)
		return ((COLOR_BLACK - COLOR_WHITE) * (i - 0) / (fractal->iterations
				- 0) + COLOR_WHITE);
	else if (fractal->color_theme == 2)
		return ((COLOR_BLACK - COLOR_DARK_GREEN) * (i - 0)
			/ (fractal->iterations - 0) + COLOR_DARK_GREEN);
	else if (fractal->color_theme == 3)
		return ((COLOR_MAGENTA - COLOR_BLUE_VIOLET) * (i - 0)
			/ (fractal->iterations - 0) + COLOR_BLUE_VIOLET);
	else if (fractal->color_theme < 1)
	{
		fractal->color_theme = 3;
		return ((COLOR_MAGENTA - COLOR_BLUE_VIOLET) * (i - 0)
			/ (fractal->iterations - 0) + COLOR_BLUE_VIOLET);
	}
	else
	{
		fractal->color_theme = 1;
		return ((COLOR_BLACK - COLOR_WHITE) * (i - 0) / (fractal->iterations
				- 0) + COLOR_WHITE);
	}
}
