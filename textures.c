#include "cub3d.h"

t_tex *get_texture(char *path, t_cub *cub)
{
    t_tex   *tex;
	void	*img;
	int		img_width;
	int		img_height;

    tex = malloc(1024);
    tex->img.img = mlx_xpm_file_to_image(cub->connection, path, &img_width, &img_height);
    tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel, &tex->img.line_length, &tex->img.endian);
    tex->ht = img_height;
    tex->wd = img_width;
    return (tex);
}

t_tex *current_texture(t_cub *cub)
{
    t_tex *tex;

    if (cub->side == 0) 
    {
        if (cub->dirX > 0)
            tex = cub->east;
        else
            tex = cub->west;
    } 
    else 
    {
        if (cub->dirY > 0)
            tex = cub->south;
        else
            tex = cub->north;
    }
    return (tex);
}

void draw_tex(int x, int start, int end, t_cub *cub)
{
    int     tex_x;
    int     tex_y;
    double  wall_x;
    double  jump;
    int     color;
    t_tex   *tex;

    tex = current_texture(cub);
    if (cub->side == 0)
        wall_x = cub->posY + cub->perpWallDist * cub->rayDirY;
    else 
        wall_x = cub->posX + cub->perpWallDist * cub->rayDirX;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)tex->wd);
    if ((cub->side == 0 && cub->dirX < 0) || 
        (cub->side == 1 && cub->dirY > 0))
        tex_x = tex->wd - tex_x - 1;
    while (start < end)
    {
        jump = tex->ht / cub->lineHeight;
        tex_y = (start - (-cub->lineHeight / 2 + screenHeight / 2)) * jump;
        color = get_texture_pixel(cub, tex_x, tex_y);
        my_mlx_pixel_put(&cub->img, x, start, color);
        start++;
    }
}

int get_texture_pixel(t_cub *cub, int x, int y)
{
    t_tex   *tex;
    int     offset;

    tex = current_texture(cub);
    
    if (x < 0 || x >= tex->wd || y < 0 || y >= tex->ht)
        return (0x000000);
        
    offset = (y * tex->img.line_length) + (x * (tex->img.bits_per_pixel / 8));
    return (*(int*)(tex->img.addr + offset));
}
