#include "../cub3d.h"

void print_validity(int texture, int rgb, t_parsing *parse)
{
    printf("\ntexture: %d\n",texture);
    printf("rgb: %d\n",rgb);
    for(int check = 0; check < 6; check++)
        printf("value: %d\n",parse->check_valid[check][0]);
    if(is_valid(parse) && texture + rgb == 6)
        printf("VALUES VALID\n");
    else
        printf("VALUES ERROR\n");
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

int check_parsing(t_parsing *parse, int *texture_count, int *rgb_count)
{
    if(!parse_map(parse))
    {
        printf("\nInvalid Map\n");
        return (0);
    }
    if(!check_txt(parse, &(*texture_count), -1, -1))
    {
        printf("\nInvalid Textures/RGB\n");
        return (0);
    }
    if(!rgb_check(parse, &(*rgb_count)))
    {
        printf("\nInvalid rgb\n");
        return 0;
    }
    return (1);
}
int check_parse(t_parsing *parse, char *file)
{
    int texture_count;
    int rgb_count;

    texture_count = 0;
    rgb_count = 0;

    get_rows(parse, file_open(file));
    if(!init_file_data(parse))
        return (0);
    get_file_data(parse, file_open(file));
    if(!get_map(parse))
        return (0);
    if(!check_parsing(parse, &texture_count, &rgb_count))
        return (0);
    print_validity(texture_count, rgb_count, parse);
    if(is_valid(parse) && texture_count + rgb_count == 6)
        return (1);
    else
        return (0);
}

int parse_init_save(char **av)
{
    int file_check;
    t_parsing *parse;

    file_check = file_open(av[1]);
        
    if(!init_parse_struct(&parse) || !file_check)
    {
        close(file_check);
        return (0);
    }
    close(file_check);
    if(!check_parse(parse, av[1]))
    {
        free_data(parse);
        return (0);
    }
    if(!save_texture(parse,file_open(av[1])) || 
        !save_rgb(parse, file_open(av[1])))
    {
        free_data(parse);
        return (0);
    }
    print_info(parse);
    free_data(parse);
    return (1);
}

int main(int ac, char **av)
{      
    if(ac == 2)
    {   
        if(!parse_init_save(av))
            return (1);
    }
    else
        printf("Invalid Args");
    return 0;
}
