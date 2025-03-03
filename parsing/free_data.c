#include "../cub3d.h"

void free_double(char **str, int size)
{
    int i;

    i = -1;
    while(++i < size && str[i] != NULL)
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
    if(parse->check_valid)
        free_int(parse->check_valid, 6);
    if(parse->textures)
    {
        if(!parse->textures[0])
            free(parse->textures);
        else
            free_double(parse->textures, 4);
    }
    if(parse->rgb)
        free_int(parse->rgb,2);
    if(parse->file_data)
        free_double(parse->file_data, parse->row);
    if(parse->map)
        free_double(parse->map, parse->map_length);
    free(parse);
}
