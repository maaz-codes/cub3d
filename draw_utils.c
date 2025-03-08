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
    while (start < end)
    {
        color_pxl(x, start, color, cub);
        start++;
    }
    while (floor < screenHeight)
    {
        color_pxl(x, floor, COLOR_PURPLE, cub);
        floor++;
    }
}
