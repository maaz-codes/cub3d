#include "cub3d.h"

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
