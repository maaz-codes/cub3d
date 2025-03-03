#include "../cub3d.h"

void check_valid_values(char *file_check, int i, t_parsing *parse, char *mode)
{   
    if(!ft_strncmp(mode,"texture",8))
    {
        if(file_check[i] == 'N' && file_check[i + 1] == 'O')
            parse->check_valid[0][0] += 1;
        else if(file_check[i] == 'S' && file_check[i + 1] == 'O')
            parse->check_valid[1][0] += 1;
        else if(file_check[i] == 'W' && file_check[i + 1] == 'E')
            parse->check_valid[2][0] += 1;
        else if(file_check[i] == 'E' && file_check[i + 1] == 'A')
            parse->check_valid[3][0] += 1;
    }
    else if(!ft_strncmp(mode,"rgb",3))
    {
        if(file_check[i] == 'F' && file_check[i + 1] == ' ')
            parse->check_valid[4][0] += 1;
        else if(file_check[i] == 'C' && file_check[i + 1] == ' ')
            parse->check_valid[5][0] += 1;
    }
}

int is_valid(t_parsing *parse)
{
    int i;
    int check;

    i = -1;
    check = 0;
    while(++i < 6)
    {
        if(parse->check_valid[i][0] == 1)
            check++;
    }
    if(check == 6)
        return 1;
    else
        return 0;
}

int init_parse_struct(t_parsing **parse)
{   
    int i;
    *parse = malloc(sizeof(t_parsing));
    if(!(*parse))
        return 0;
    (*parse)->check_valid = malloc(6 * sizeof(int **));
    if(!(*parse)->check_valid)
        return 0;
    i = -1;
    while(++i < 6)
    {
        (*parse)->check_valid[i] = malloc(1 * sizeof(int*));
        if(!(*parse)->check_valid[i])
            return (0);
        *(*parse)->check_valid[i] = 0;
    }
    if(!init_textures_and_rgb(parse))
        return (0);
    return 1;
}

int file_open(char *av)
{   
    int file;
    file = open(av,O_RDONLY);
    if(file == -1)
    {
        printf("Invalid file\n");
        return (0);
    }
    return(file);
}

int init_file_data(t_parsing *parse)
{
    parse->file_data = malloc((parse->row + 1) * sizeof(char **));
    if(!parse->file_data)
        return(0);
    parse->file_data[parse->row] = NULL;
    return (1);
}