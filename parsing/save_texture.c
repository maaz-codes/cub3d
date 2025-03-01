#include "../cub3d.h"

int init_textures_and_rgb(t_parsing **parse)
{
    int i;
    int f;
    i = -1;
    (*parse)->textures = malloc(4 * sizeof(char *));
    if(!(*parse)->textures)
        return (0);
    (*parse)->rgb = malloc(2 * sizeof(int *));
    if(!(*parse)->rgb)
        return(0);
    while(++i < 2)
    {   
        f = -1;
        (*parse)->rgb[i] = malloc(3 * sizeof(int));
            if(!(*parse)->rgb[i])
                return(0);
        while(++f < 3)
            (*parse)->rgb[i][f] = 0;
    }
    return (1);
}

int append_texture(char *file_check, int *i, int txt_index, t_parsing *parse)
{
    int len_count;

    len_count = 0;
    (*i) += 2;
    while(file_check[(*i)] == ' ')
        (*i) += 1;
    while(file_check[(*i)] != ' ' && file_check[(*i)] && file_check[(*i)] != '\n')
    {   
        len_count++;
        (*i) += 1;
    }
    parse->textures[txt_index - 1] = ft_calloc(len_count + 1,sizeof(char *));
    if(!parse->textures[txt_index - 1])
        return (0);
    ft_strlcpy(parse->textures[txt_index - 1], file_check + ((*i) - len_count), len_count + 1);
    return (1);
}

int save_texture(t_parsing *parse, int file)
{
    char *file_check;
    int txt_index;
    int i;

    file_check = get_next_line(file);
    while(file_check)
    {   
        i = -1;
        while(++i < ft_strlen(file_check))
        {
            if(check_which_texture(file_check, i) < 5 && 
                check_which_texture(file_check, i) != 0)
            {   
                txt_index = check_which_texture(file_check, i);
                if(!append_texture(file_check, &i, txt_index, parse))
                    return (0);
            }
        }
        free(file_check);
        file_check = get_next_line(file);
    }
    close(file);
    return 1;
}
