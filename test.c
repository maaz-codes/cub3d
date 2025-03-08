#include "cub3d.h"

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