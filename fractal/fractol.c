/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:01:57 by maakhan           #+#    #+#             */
/*   Updated: 2025/02/18 16:25:19 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_fractal(t_fractal *fractal)
{
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1;
}

int	handle_closing(t_fractal *fractal)
{
	mlx_destroy_window(fractal->connection, fractal->win);
	free(fractal->connection);
	exit(0);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->connection = mlx_init();
	fractal->win = mlx_new_window(fractal->connection, screenWidth, screenHeight,
			fractal->name);
	fractal->img.img = mlx_new_image(fractal->connection, screenWidth,
			screenHeight);
	fractal->img.addr = mlx_get_data_addr(fractal->img.img,
			&fractal->img.bits_per_pixel, &fractal->img.line_length,
			&fractal->img.endian);
	fractal->zoom = 1;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->iterations = 50;
	fractal->motion_flag = 0;
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac >= 2)
	{
		if (!check_args(ac, av, &fractal))
			return (fractal_menu());
		fractal_init(&fractal);
		fractal_rendering(&fractal);
		mlx_loop_hook(fractal.connection, handle_no_event, &fractal);
		mlx_key_hook(fractal.win, handle_key_release, &fractal);
		mlx_mouse_hook(fractal.win, handle_mouse_click, &fractal);
		mlx_hook(fractal.win, 6, 6, handle_mouse_motion, &fractal);
		mlx_hook(fractal.win, 17, 6, handle_closing, &fractal);
		mlx_loop(fractal.connection);
		mlx_destroy_window(fractal.connection, fractal.win);
		free(fractal.connection);
	}
	else
		return (fractal_menu());
}
