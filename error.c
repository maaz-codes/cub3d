#include "cub3d.h"

void free_textures(t_cub *cub)
{
    if (cub->north)
    {
        if (cub->north->img.img)
            mlx_destroy_image(cub->connection, cub->north->img.img);
        free(cub->north);
    }
    if (cub->south)
    {
        if (cub->south->img.img)
            mlx_destroy_image(cub->connection, cub->south->img.img);
        free(cub->south);
    }
    if (cub->east)
    {
        if (cub->east->img.img)
            mlx_destroy_image(cub->connection, cub->east->img.img);
        free(cub->east);
    }
    if (cub->west)
    {
        if (cub->west->img.img)
            mlx_destroy_image(cub->connection, cub->west->img.img);
        free(cub->west);
    }
}

// void free_map(t_cub *cub)
// {
//     int i;

//     i = 0;
//     while (cub->final_map[i])
//     {
//         free(cub->final_map[i]);
//         i++;
//     }
//     free(cub->final_map);
// }

int error_msg(int flag)
{
    if (flag == ERR_MALLOC)
        write(2, "Malloc failed\n", 15);
    else if (flag == ERR_FILE)
        write(2, "File error\n", 12);
    else if (flag == ERR_SYS_ARGS)
        write(2, "Arguments error\n", 17);
    else if (flag == ERR_MLX)
        write(2, "Mlx function error\n", 20);
    return (EXIT_FAILURE);
}   

void cub_slayer(t_cub *cub)
{
    // free_map(cub);
    free_textures(cub);
    mlx_destroy_image(cub->connection, cub->img.img);
    mlx_destroy_window(cub->connection, cub->win);
    free(cub->connection);
    free(cub);
}
