/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:12 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/06 18:15:04 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_motion(double move_x, double move_y, t_cub *cub)
{
	if (move_x > 1 || move_y > 1 || move_y < cub->parse->map_length
		|| move_x < (int)ft_strlen(cub->parse->map[(int)move_y]))
	{
		if (cub->map[(int)move_y][(int)cub->pos_x] == WALKABLE)
			cub->pos_y = move_y;
		if (cub->map[(int)cub->pos_y][(int)move_x] == WALKABLE)
			cub->pos_x = move_x;
	}
}

void	rotation(int dir, t_cub *cub)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	if (dir == KEY_RIGHT)
		rot = ROT_SPEED;
	else
		rot = -ROT_SPEED;
	cos_rot = cos(rot);
	sin_rot = sin(rot);
	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos_rot - cub->dir_y * sin_rot;
	cub->dir_y = old_dir_x * sin_rot + cub->dir_y * cos_rot;
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos_rot - cub->plane_y * sin_rot;
	cub->plane_y = old_plane_x * sin_rot + cub->plane_y * cos_rot;
}

void	motion(double *mx, double *my, int dir, t_cub *cub)
{
	if (dir == KEY_W)
	{
		*mx = cub->pos_x + (cub->dir_x * MOVE_SPEED);
		*my = cub->pos_y + (cub->dir_y * MOVE_SPEED);
	}
	else if (dir == KEY_S)
	{
		*mx = cub->pos_x - (cub->dir_x * MOVE_SPEED);
		*my = cub->pos_y - (cub->dir_y * MOVE_SPEED);
	}
	else if (dir == KEY_D)
	{
		*mx = cub->pos_x + (cub->plane_x * MOVE_SPEED);
		*my = cub->pos_y + (cub->plane_y * MOVE_SPEED);
	}
	else if (dir == KEY_A)
	{
		*mx = cub->pos_x - (cub->plane_x * MOVE_SPEED);
		*my = cub->pos_y - (cub->plane_y * MOVE_SPEED);
	}
}
