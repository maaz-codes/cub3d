#include "cub3d.h"

void init_direction(t_cub *cub, int direc)
{
    cub->dirX = 0;
    cub->dirY = 0;
    cub->planeX = 0;
    cub->planeY = 0;
    if (direc == 'W')
    {
        cub->dirY = -1;
        cub->planeX = 0.66;
    }
    else if (direc == 'E')
    {
        cub->dirY = 1;
        cub->planeX = -0.66;
    }
    else if (direc == 'S')
    {
        cub->dirX = 1;
        cub->planeY = 0.66;
    }
    else if (direc == 'N')
    {
        cub->dirX = -1;
        cub->planeY = 0.66;
    }
}

void init_textures(t_cub *cub)
{
    cub->north = get_texture("./textures/purple_tex.xpm", cub);
    cub->south = get_texture("./textures/green_tex.xpm", cub);
    cub->east = get_texture("./textures/red_tex.xpm", cub);
    cub->west = get_texture("./textures/green_tex.xpm", cub);
}

void cub_init(t_cub *cub)
{
    cub->connection = mlx_init();
    cub->win = mlx_new_window(cub->connection, screenWidth, screenHeight, "cub3D");
    cub->img.img = mlx_new_image(cub->connection, screenWidth, screenHeight);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
    cub->direc = 'E';
    init_direction(cub, cub->direc);
    cub->posX = 1 + 0.5;
    cub->posY = 1 + 0.5;
    init_textures(cub);
    cub->ceil = COLOR_WHITE;
    cub->floor = COLOR_YELLOW;
    cub->map_ht = mapHeight;
    cub->map_wd = mapWidth;
}

int cub_rendering(t_cub *cub)
{
    int x = 0;
    int y = 0;

    while (x < screenWidth)
    {
        //calculate ray position and direction
        perform_ray_casting(x, cub);
        perform_dda(cub);
        if (cub->side == 0) 
            cub->perpWallDist = (cub->sideDistX - cub->deltaDistX);
        else          
            cub->perpWallDist = (cub->sideDistY - cub->deltaDistY);
        get_drawing_coords(cub);
        draw_strip(x, cub->drawStart, cub->drawEnd, cub);
        x++;
    }
    mlx_put_image_to_window(cub->connection, cub->win, cub->img.img, 0, 0);
    return (1);
}

int main(int ac, char **av)
{
    t_cub *cub;

    char worldMap[mapHeight][mapWidth] =
    {
        {"1111111111"},
        {"1000000001"},
        {"1000010001"},
        {"1000010001"},
        {"1111111111"}
    };
    cub = (t_cub *)malloc(sizeof(t_cub));
    if (!cub)
        exit(error_msg(ERR_MALLOC));
    cub->map = worldMap;
    cub_init(cub);
    mlx_hook(cub->win, ON_KEY_UP, MASK_KEY_UP, handle_key_event, cub);
    mlx_hook(cub->win, ON_DESTROY, MASK_ON_DESTROY, handle_closing, cub);
	mlx_loop_hook(cub->connection, cub_rendering, cub);
    mlx_loop(cub->connection);
    cub_slayer(cub);
}
