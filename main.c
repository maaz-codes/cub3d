#include "cub3d.h"

int rgb_to_int(int *color)
{
    return (color[0] << 16) | (color[1] << 8) | color[2];
}

void cub_spawner(t_cub *cub)
{
    cub->connection = NULL;
    cub->img.img = NULL;
    cub->img.addr = NULL;
    cub->north = NULL;
    cub->south = NULL;
    cub->east = NULL;
    cub->west = NULL;
}

void cub_init(t_cub *cub, t_parsing *parse)
{
    cub->connection = mlx_init();
    cub->win = mlx_new_window(cub->connection, screenWidth, screenHeight, "cub3D");
    cub->img.img = mlx_new_image(cub->connection, screenWidth, screenHeight);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
    cub->direc = parse->player;
    init_direction(cub, cub->direc);
    cub->posX = parse->x_pos + 0.5;
    cub->posY = parse->y_pos + 0.5;
    init_textures(cub, parse);
    cub->floor = rgb_to_int(parse->rgb[0]);
    cub->ceil = rgb_to_int(parse->rgb[1]);
    cub->parse = parse;
}

int cub_rendering(t_cub *cub)
{
    int x = 0;
    int y = 0;

    while (x < screenWidth)
    {
        //calculate ray position and direction
        perform_ray_casting(x, cub);
        perform_dda(cub, cub->parse);
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
    t_cub       *cub;
    t_parsing   *parse;

    if(ac == 2)
    {   
        if(!valid_cub_file(av[1]))
            return (0);
        if(!parse_init_save(&parse, av))
            return (free_data(parse), 0);
        cub = (t_cub *)malloc(sizeof(t_cub));
        if (!cub)
            exit(error_msg(ERR_MALLOC));
        cub->map = parse->map;
        cub_spawner(cub);
        cub_init(cub, parse);
        mlx_hook(cub->win, ON_KEY_UP, MASK_KEY_UP, handle_key_event, cub);
        mlx_hook(cub->win, ON_DESTROY, MASK_ON_DESTROY, handle_closing, cub);
        mlx_loop_hook(cub->connection, cub_rendering, cub);
        mlx_loop(cub->connection);
        free_data(parse);
    }
    else
        printf("Invalid Args\n");
}
