/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:28:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/08/31 12:47:47 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(char *num1, char *num2, t_fractal *fractal)
{
	fractal->name = "julia";
	if (!check_complex(num1) || !check_complex(num2))
		return (0);
	fractal->julia_x = ft_atof(num1);
	fractal->julia_y = ft_atof(num2);
	return (1);
}

void	algo_julia(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.x = (scale(x, -2, 2) * fractal->zoom) + fractal->shift_x;
	z.y = (scale(y, 2, -2) * fractal->zoom) + fractal->shift_y;
	c.x = fractal->julia_x;
	c.y = fractal->julia_y;
	i = 0;
	while (i < fractal->iterations)
	{
		z = add_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > ESCAPE_VALUE)
		{
			color = (COLOR_BLACK - COLOR_WHITE) * (i - 0) / (fractal->iterations
					- 0) + COLOR_WHITE;
			my_mlx_pixel_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_mlx_pixel_put(&fractal->img, x, y, COLOR_BLACK);
}
