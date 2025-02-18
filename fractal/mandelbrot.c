/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:29:04 by maakhan           #+#    #+#             */
/*   Updated: 2024/09/29 11:26:45 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_fractal *fractal)
{
	fractal->name = "mandelbrot";
	fractal->julia_x = 0;
	fractal->julia_y = 0;
	return (1);
}

void	algo_mandelbrot(int x, int y, t_fractal *fractal)
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
		z = add_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > ESCAPE_VALUE)
		{
			color = (COLOR_BLACK - COLOR_BLUE_VIOLET) * (i - 0) / (fractal->iterations
					- 0) + COLOR_WHITE;
			my_mlx_pixel_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_mlx_pixel_put(&fractal->img, x, y, COLOR_BLACK);
}
