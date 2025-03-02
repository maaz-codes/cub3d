#include "../cub3d.h"

void error_msg(char *str)
{
    printf("%s\n",str);
}

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
        error_msg("Invalid file\n");
    return(file);
}

int check_parse(t_parsing *parse, char *file)
{
    int texture_count;
    int rgb_count;

    texture_count = 0;
    rgb_count = 0;

    get_rows(parse, file_open(file));
    parse->file_data = malloc((parse->row + 1) * sizeof(char **));
    if(!parse->file_data)
        return(0);
    parse->file_data[parse->row] = NULL;
    get_file_data(parse, file_open(file));
    if(!get_map(parse))
        return (0);
    if(!parse_map(parse))
    {
        printf("\nerror map\n");
        return (0);
    }
    if(!check_txt(parse, &texture_count))
    {
        printf("error textures\n");
        return (0);
    }
    if(!rgb_check(parse, &rgb_count))
    {
        error_msg("Invalid rgb\n");
        return 0;
    }
    printf("\ncontent: %d\n",texture_count);
    printf("\ncontent: %d\n",rgb_count);
    for(int check = 0; check < 6; check++)
        printf("value: %d\n",parse->check_valid[check][0]);
    if(is_valid(parse) && texture_count + rgb_count == 6)
    {
        printf("VALUES VALID\n");
        return (1);
    }
    else
    {
        printf("VALUES ERROR\n");
        return (0);
    }
}

void print_info(t_parsing *parse)
{   
    for(int f = 0; f < 4; f++)
        printf("textures : %s\n",parse->textures[f]);
    for(int f = 0; f < 2; f++)
    {   
        printf("rgb %d ",f);
        for(int x = 0; x < 3; x++)
        {
            printf("%d ",parse->rgb[f][x]);
        }
        printf("\n");
    }
}
int main(int ac, char **av)
{      
    t_parsing *parse;

    if(ac == 2)
    {   
        if(!init_parse_struct(&parse))
            return 1;
        if(!check_parse(parse, av[1]))
        {
            printf("Invalid\n");
            return 1;
        }
        if(!save_texture(parse,file_open(av[1])))
        {
            printf("Invalid texture\n");
            return 1;
        }
        if(!save_rgb(parse, file_open(av[1])))
        {
            printf("Invalid number\n");
            return 1;
        }
        print_info(parse);
        free_data(parse);
    }
    else
        error_msg("Invalid Args");
    return 0;
}
