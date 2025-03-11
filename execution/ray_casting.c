/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:12 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/06 18:15:04 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	perform_dda(t_cub *cub, t_parsing *parse)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		if (cub->map_x < 0 || cub->map_y < 0 || cub->map_y >= parse->map_length
			|| cub->map_x >= (int)ft_strlen(parse->map[cub->map_y]))
			hit = 1;
		else if (cub->map[cub->map_y][cub->map_x] == '1')
			hit = 1;
	}
}

void	init_rays(int x, t_cub *cub)
{
	cub->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	cub->ray_dir_x = cub->dir_x + cub->plane_x * cub->camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * cub->camera_x;
	cub->map_x = (int)cub->pos_x;
	cub->map_y = (int)cub->pos_y;
	if (cub->ray_dir_x == 0)
		cub->delta_dist_x = 1e30;
	else
		cub->delta_dist_x = fabs(1 / cub->ray_dir_x);
	if (cub->ray_dir_y == 0)
		cub->delta_dist_y = 1e30;
	else
		cub->delta_dist_y = fabs(1 / cub->ray_dir_y);
}

void	perform_ray_casting(int x, t_cub *cub)
{
	init_rays(x, cub);
	if (cub->ray_dir_x < 0)
	{
		cub->step_x = -1;
		cub->side_dist_x = (cub->pos_x - cub->map_x) * cub->delta_dist_x;
	}
	else
	{
		cub->step_x = 1;
		cub->side_dist_x = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dist_x;
	}
	if (cub->ray_dir_y < 0)
	{
		cub->step_y = -1;
		cub->side_dist_y = (cub->pos_y - cub->map_y) * cub->delta_dist_y;
	}
	else
	{
		cub->step_y = 1;
		cub->side_dist_y = (cub->map_y + 1.0 - cub->pos_y) * cub->delta_dist_y;
	}
}

void	init_direction(t_cub *cub, int direc)
{
	cub->dir_x = 0;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0;
	if (direc == 'N')
	{
		cub->dir_y = -1;
		cub->plane_x = 0.66;
	}
	else if (direc == 'S')
	{
		cub->dir_y = 1;
		cub->plane_x = -0.66;
	}
	else if (direc == 'E')
	{
		cub->dir_x = 1;
		cub->plane_y = 0.66;
	}
	else if (direc == 'W')
	{
		cub->dir_x = -1;
		cub->plane_y = 0.66;
	}
}
