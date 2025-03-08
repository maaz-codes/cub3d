#include "cub3d.h"

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

int get_pixel_color(t_cub *cub, int x, int y)
{
    t_tex   *tex;
    int     offset;
    
    // Select texture based on wall direction
    if (cub->side == 0) {
        if (cub->dirX > 0)
            tex = cub->north;
        else
            tex = cub->north;
    } else {
        if (cub->dirY > 0)
            tex = cub->north;
        else
            tex = cub->north;
    }
    
    // Bounds checking
    if (x < 0 || x >= tex->wd || y < 0 || y >= tex->ht)
        return (0x000000);
        
    offset = (y * tex->img.line_length) + (x * (tex->img.bits_per_pixel / 8));
    return (*(int*)(tex->img.addr + offset));
}

void draw_tex(int x, int start, int end, t_cub *cub)
{
    int     tex_x;
    int     tex_y;
    double  wall_x;
    double  jump;
    int     color;

    if (cub->side == 0)
        wall_x = cub->posY + cub->perpWallDist * cub->rayDirY;
    else 
        wall_x = cub->posX + cub->perpWallDist * cub->rayDirX;

    wall_x -= floor(wall_x);
    // calculate the x-coord of tex
    tex_x = (int)(wall_x * (double)cub->north->wd);
    // flip x-coord of tex if needed
    if ((cub->side == 0 && cub->dirX < 0) ||
        (cub->side == 1 && cub->dirY > 0))
        tex_x = cub->north->wd - tex_x - 1;
    while (start < end)
    {
        jump = cub->north->ht / cub->lineHeight;
        // calculate the y-coord of tex
        tex_y = (start - (-cub->lineHeight / 2 + screenHeight / 2)) * jump;
        color = get_pixel_color(cub, tex_x, tex_y);
        my_mlx_pixel_put(&cub->img, x, start, color);
        start++;
    }
}

void 	draw_strip(int x, int start, int end, int color, t_cub *cub)
{
    int ceil;
    int floor;

    ceil = 0;
    floor = end;
    while (ceil < start)
    {
        color_pxl(x, ceil, COLOR_MAGENTA, cub);
        ceil++;
    }
    draw_tex(x, start, end, cub);
    // while (start < end)
    // {
    //     color_pxl(x, start, color, cub);
    //     start++;
    // }
    while (floor < screenHeight)
    {
        color_pxl(x, floor, COLOR_PURPLE, cub);
        floor++;
    }
}

int get_color(t_cub *cub)
{
    int dir;
    int color;

    dir = cub->map[cub->mapX][cub->mapY];
    if (dir == 1)
        color = COLOR_RED;
    else if (dir == 2)
        color = COLOR_GREEN;
    else if (dir == 3)
        color = COLOR_BLUE;
    else if (dir == 4)
        color = COLOR_WHITE;
    else
        color = COLOR_YELLOW;
    if (cub->side == 1)
        color /= 2;
    return (color);
}

void get_drawing_coords(t_cub *cub)
{
    cub->lineHeight = (int)(screenHeight / cub->perpWallDist);
    cub->drawStart = -cub->lineHeight / 2 + screenHeight / 2;
    if(cub->drawStart < 0) 
        cub->drawStart = 0;
    cub->drawEnd = cub->lineHeight / 2 + screenHeight / 2;
    if(cub->drawEnd >= screenHeight)
        cub->drawEnd = screenHeight - 1;
}
