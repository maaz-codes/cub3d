/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:12 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/06 18:15:04 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	color_pxl(int x, int y, int color, t_cub *cub)
{
	my_mlx_pixel_put(&cub->img, x, y, color);
}

void	draw_strip(int x, int start, int end, t_cub *cub)
{
	int	ceil;
	int	floor;

	ceil = 0;
	floor = end;
	while (ceil < start + 10)
	{
		color_pxl(x, ceil, cub->ceil, cub);
		ceil++;
	}
	draw_tex(x, start, end, cub);
	while (floor < SCREENHEIGHT)
	{
		color_pxl(x, floor, cub->floor, cub);
		floor++;
	}
}

void	get_drawing_coords(t_cub *cub)
{
	cub->line_height = (int)(SCREENHEIGHT / cub->perp_wall_dist);
	cub->draw_start = -cub->line_height / 2 + SCREENHEIGHT / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + SCREENHEIGHT / 2;
	if (cub->draw_end >= SCREENHEIGHT)
		cub->draw_end = SCREENHEIGHT - 1;
}
