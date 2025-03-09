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

void 	draw_strip(int x, int start, int end, t_cub *cub)
{
    int ceil;
    int floor;

    ceil = 0;
    floor = end;
    while (ceil < start + 10)
    {
        if ((rand() % 10000) + 1 == 1)
            color_pxl(x, ceil, COLOR_WHITE, cub);
        else if ((rand() % 10000) + 1 == 2)
            color_pxl(x, ceil, COLOR_PURPLE, cub);
        else
            color_pxl(x, ceil, cub->ceil, cub);
        ceil++;
    }
    while (floor < screenHeight)
    {
        if (floor % 10 == 0)
            color_pxl(x, floor, COLOR_BLACK, cub);
        else
            color_pxl(x, floor, cub->floor, cub);
        floor++;
    }
    draw_tex(x, start, end, cub);
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
