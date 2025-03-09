#include "cub3d.h"

void init_textures(t_cub *cub)
{
    cub->north = get_texture("./textures/purple_tex.xpm", cub);
    cub->south = get_texture("./textures/green_tex.xpm", cub);
    cub->east = get_texture("./textures/red_tex.xpm", cub);
    cub->west = get_texture("./textures/green_tex.xpm", cub);
}

t_tex *get_texture(char *path, t_cub *cub)
{
    t_tex   *tex;
	int		img_width;
	int		img_height;

    tex = (t_tex *)malloc(sizeof(t_tex));
    if (!tex)
    {
        // malloc_failed code...
        // free full cub struct...
        // exit...
        cub_slayer(cub);
        exit(error_msg(ERR_MALLOC));
    }
    tex->img.img = mlx_xpm_file_to_image(cub->connection, path, &img_width, &img_height);
    if (!tex->img.img)
    {
        cub_slayer(cub);
        error_msg(ERR_FILE);
        exit(EXIT_FAILURE);
    }
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
        if (cub->rayDirX > 0)
            tex = cub->south;
        else
            tex = cub->north;
    } 
    else 
    {
        if (cub->rayDirY > 0)
            tex = cub->east;
        else
            tex = cub->west;
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
        color_pxl(x, start, color, cub);
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
