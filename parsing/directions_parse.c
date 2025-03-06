#include "../cub3d.h"

int check_if_direction(char *file_check, int i)
{
    if(file_check[i] == 'N' && file_check[i + 1] == 'O')
        return 1;
    else if(file_check[i] == 'S' && file_check[i + 1] == 'O')
        return 1;
    else if(file_check[i] == 'W' && file_check[i + 1] == 'E')
        return 1;
    else if(file_check[i] == 'E' && file_check[i + 1] == 'A')
        return 1;
    else if(file_check[i] == 'F')
        return 1;
    else if(file_check[i] == 'C')
        return 1;
    return 0;
}

int check_valid_rgb(char *file_check, int *i)
{   
    while(file_check[++(*i)] == ' ' && file_check[*i])
    if(!file_check[*i])
        break;
    while(file_check[++(*i)])
    {
        if(file_check[*i] >= '0' && file_check[*i] <= '9')
            continue;
        else
            break;
    }
    while(file_check[*i] == ' ' && file_check[*i])
        (*i)++;
    if(file_check[*i] == ',')
        return (1);
    else
        return (0);
}

int parse_rgb_numbers(char *file_check, int *i)
{
    while(file_check[(*i)] >= '0' && file_check[(*i)] <= '9')
        (*i)++;
    while(file_check[(*i)] == ' ' && file_check[(*i)])
        (*i)++;
    if(file_check[(*i)] == ',')
        return 1;
    return 0;
}
