/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:01:34 by maakhan           #+#    #+#             */
/*   Updated: 2024/08/31 11:43:26 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_no_event(t_fractal *fractal)
{
	fractal_rendering(fractal);
	mlx_put_image_to_window(fractal->connection, fractal->win, fractal->img.img,
		0, 0);
	return (1);
}

int	handle_key_release(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_LEFT)
		fractal->shift_x += 0.1 * fractal->zoom;
	else if (keycode == KEY_RIGHT)
		fractal->shift_x -= 0.1 * fractal->zoom;
	else if (keycode == KEY_UP)
		fractal->shift_y -= 0.1 * fractal->zoom;
	else if (keycode == KEY_DOWN)
		fractal->shift_y += 0.1 * fractal->zoom;
	else if (keycode == KEY_SPACE_BAR)
		reset_fractal(fractal);
	else if (keycode == KEY_I)
		fractal->iterations += 10;
	else if (keycode == KEY_O)
	{
		if (fractal->iterations > 10)
			fractal->iterations -= 10;
	}
	else if (keycode == KEY_P)
		fractal->motion_flag = !fractal->motion_flag;
	else if (keycode == KEY_ESC)
		handle_closing(fractal);
	fractal_rendering(fractal);
	return (1);
}

int	handle_mouse_motion(int mouse_x, int mouse_y, t_fractal *fractal)
{
	double	x;
	double	y;

	x = (scale(mouse_x, -2, 2) * fractal->zoom)
		+ fractal->shift_x;
	y = (scale(mouse_y, 2, -2) * fractal->zoom)
		+ fractal->shift_y;
	if (fractal->motion_flag)
	{
		fractal->julia_x = x;
		fractal->julia_y = y;
	}
	return (1);
}

int	handle_mouse_click(int keycode, int mouse_x, int mouse_y,
		t_fractal *fractal)
{
	mlx_mouse_get_pos(fractal->win, &mouse_x, &mouse_y);
	if (keycode == 5)
		fractal->zoom /= 1.25;
	else if (keycode == 4)
		fractal->zoom *= 1.25;
	fractal_rendering(fractal);
	return (1);
}
