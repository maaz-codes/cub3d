#include "cub3d.h"

void cub_init(t_cub *cub, t_parsing *parse)
{
    cub->connection = mlx_init();
    cub->win = mlx_new_window(cub->connection, screenWidth, screenHeight, "cub3D");
    cub->img.img = mlx_new_image(cub->connection, screenWidth, screenHeight);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);

    cub->posX = parse->x_pos;
    cub->posY = parse->y_pos;

    cub->dirX = -1;
    cub->dirY = 0;

    cub->planeX = 0;
    cub->planeY = 0.66;
}

void print_map(char **map)
{
    int i = 0;

    while (i < 5)
    {
        int j = 0;
        while (j < 10)
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

unsigned long getTicks(t_cub *cub) 
{
    struct timeval tv;
    struct timeval tick;

    gettimeofday(&tv, NULL);
    tick.tv_sec = tv.tv_sec - cub->start_time.tv_sec;
    tick.tv_usec = tv.tv_usec - cub->start_time.tv_usec;
    return (tick.tv_sec * 1000) + (tick.tv_usec / 1000); // Convert to milliseconds
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

void perform_dda(t_cub *cub)
{
    int hit;

    hit = 0;
    while(hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if(cub->sideDistX < cub->sideDistY)
        {
            cub->sideDistX += cub->deltaDistX;
            cub->mapX += cub->stepX;
            cub->side = 0;
        }
        else
        {
            cub->sideDistY += cub->deltaDistY;
            cub->mapY += cub->stepY;
            cub->side = 1;
        }
        //Check if ray has hit a wall
        if(cub->map[cub->mapX][cub->mapY] > '0') 
            hit = 1;
    }
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

void init_rays(int x, t_cub *cub)
{
    cub->cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
    cub->rayDirX = cub->dirX + cub->planeX * cub->cameraX;
    cub->rayDirY = cub->dirY + cub->planeY * cub->cameraX;
    cub->mapX = (int)cub->posX;
    cub->mapY = (int)cub->posY; 
    if (cub->rayDirX == 0)
        cub->deltaDistX = 1e30;
    else
        cub->deltaDistX = fabs(1 / cub->rayDirX);
    if (cub->rayDirY == 0)
        cub->deltaDistY = 1e30;
    else
        cub->deltaDistY = fabs(1 / cub->rayDirY);
}

void perform_ray_casting(int x, t_cub *cub)
{
    init_rays(x, cub);
    if(cub->rayDirX < 0)
    {
        cub->stepX = -1;
        cub->sideDistX = (cub->posX - cub->mapX) * cub->deltaDistX;
    }
    else
    {
        cub->stepX = 1;
        cub->sideDistX = (cub->mapX + 1.0 - cub->posX) * cub->deltaDistX;
    }
    if(cub->rayDirY < 0)
    {
        cub->stepY = -1;
        cub->sideDistY = (cub->posY - cub->mapY) * cub->deltaDistY;
    }
    else
    {
        cub->stepY = 1;
        cub->sideDistY = (cub->mapY + 1.0 - cub->posY) * cub->deltaDistY;
    }
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
        cub->color = get_color(cub);
        draw_strip(x, cub->drawStart, cub->drawEnd, cub->color, cub);   
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
        // cub = (t_cub *)malloc(1024 * 100);
        // cub->map = parse->map;
        // cub_init(cub, parse);
        // cub_rendering(cub);
        // mlx_key_hook(cub->win, handle_key_release, cub);
        // mlx_loop(cub->connection);
        // free(cub->connection);
        free_data(parse);
    }
    else
        printf("Invalid Args\n");
}
