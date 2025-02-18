/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:02:12 by maakhan           #+#    #+#             */
/*   Updated: 2025/02/18 16:25:19 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	color_pxl(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "mandelbrot", 11))
		algo_mandelbrot(x, y, fractal);
	else if (!ft_strncmp(fractal->name, "julia", 6))
		algo_julia(x, y, fractal);
}

void	fractal_rendering(t_fractal *fractal)
{
	int	x;
	int	y;

	x = 0;
	while (x < screenWidth)
	{
		y = 0;
		while (y < screenHeight)
		{
			color_pxl(x, y, fractal);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractal->connection, fractal->win, fractal->img.img,
		0, 0);
}
