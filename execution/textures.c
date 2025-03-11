/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:12 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/06 18:15:04 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures(t_cub *cub, t_parsing *parse)
{
	cub->west = get_texture(ft_strjoin("./", parse->textures[0]), cub);
	cub->east = get_texture(ft_strjoin("./", parse->textures[1]), cub);
	cub->north = get_texture(ft_strjoin("./", parse->textures[2]), cub);
	cub->south = get_texture(ft_strjoin("./", parse->textures[3]), cub);
}

t_tex	*get_texture(char *path, t_cub *cub)
{
	t_tex	*tex;
	int		img_width;
	int		img_height;

	tex = (t_tex *)malloc(sizeof(t_tex));
	if (!tex)
	{
		(free(path), free_data(cub->parse));
		cub_slayer(cub);
		exit(error_msg(ERR_MALLOC));
	}
	tex->img.img = mlx_xpm_file_to_image(cub->connection, path,
			&img_width, &img_height);
	free(path);
	if (!tex->img.img)
	{
		(free_data(cub->parse), cub_slayer(cub));
		error_msg(ERR_FILE);
		exit(EXIT_FAILURE);
	}
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
			&tex->img.line_length, &tex->img.endian);
	tex->ht = img_height;
	tex->wd = img_width;
	return (tex);
}

t_tex	*current_texture(t_cub *cub)
{
	t_tex	*tex;

	if (cub->side == 0)
	{
		if (cub->ray_dir_x > 0)
			tex = cub->south;
		else
			tex = cub->north;
	}
	else
	{
		if (cub->ray_dir_y > 0)
			tex = cub->east;
		else
			tex = cub->west;
	}
	return (tex);
}

void	draw_tex(int x, int start, int end, t_cub *cub)
{
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	jump;
	t_tex	*tex;

	tex = current_texture(cub);
	if (cub->side == 0)
		wall_x = cub->pos_y + cub->perp_wall_dist * cub->ray_dir_y;
	else
		wall_x = cub->pos_x + cub->perp_wall_dist * cub->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->wd);
	if ((cub->side == 0 && cub->dir_x < 0)
		|| (cub->side == 1 && cub->dir_y > 0))
		tex_x = tex->wd - tex_x - 1;
	while (start < end)
	{
		jump = tex->ht / cub->line_height;
		tex_y = (start - (-cub->line_height / 2 + SCREENHEIGHT / 2)) * jump;
		color_pxl(x, start, get_texture_pixel(cub, tex_x, tex_y), cub);
		start++;
	}
}

int	get_texture_pixel(t_cub *cub, int x, int y)
{
	t_tex	*tex;
	int		offset;

	tex = current_texture(cub);
	if (x < 0 || x >= tex->wd || y < 0 || y >= tex->ht)
		return (0x000000);
	offset = (y * tex->img.line_length) + (x * (tex->img.bits_per_pixel / 8));
	return (*(int *)(tex->img.addr + offset));
}
