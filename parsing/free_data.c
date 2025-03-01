#include "../cub3d.h"

void free_double(char **str, int size)
{
    int i;

    i = -1;
    while(++i < size)
        free(str[i]);
    free(str);
}

void free_int(int **num, int size)
{
    int i;

    i = -1;
    while(++i < size)
        free(num[i]);
    free(num);
}

void free_data(t_parsing *parse)
{
    free_int(parse->check_valid,6);
    free_double(parse->textures,4);
    free_int(parse->rgb,2);
    free(parse);
}