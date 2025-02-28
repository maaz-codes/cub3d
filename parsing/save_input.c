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

int save_texture(t_parsing *parse, int file)
{
    char *file_check;
    int txt_index;
    int i;
    int len_count;

    file_check = get_next_line(file);
    while(file_check)
    {   
        i = -1;
        len_count = 0;
        while(++i < ft_strlen(file_check))
        {
            if(check_which_texture(file_check, i) < 5 && 
                check_which_texture(file_check, i) != 0)
            {   
                txt_index = check_which_texture(file_check, i);
                i += 1;
                while(file_check[++i] == ' ');
                while(file_check[i] != ' ' && file_check[i] && file_check[i] != '\n')
                {   
                    len_count++;
                    i++;
                }
                parse->textures[txt_index - 1] = ft_calloc(len_count + 1,sizeof(char *));
                if(!parse->textures[txt_index - 1])
                    return (0);
                ft_strlcpy(parse->textures[txt_index - 1], file_check + (i - len_count), len_count + 1);
            }
        }
        file_check = get_next_line(file);
    }
    close(file);
    return 1;
}

int save_rgb(t_parsing *parse, int file)
{
    char *file_check;
    char *temp;
    int len_count;
    int rgb_row;
    int rgb_column;
    int i;

    file_check = get_next_line(file);
    while(file_check)
    {   
        i = -1;
        rgb_column = 0;
        len_count = 0;
        while(++i < ft_strlen(file_check))
        {   
            if(check_which_texture(file_check, i) > 4)
            {   
                rgb_row = check_which_texture(file_check, i);
                i += 1;
                while(file_check[i] != '\n' && file_check[i])
                {
                    while(file_check[++i] == ' ' && file_check[i] == ',');
                    while(file_check[i] != ' ' && file_check[i] && file_check[i] != '\n' 
                        && file_check[i] != ',')
                    {   
                        len_count++;
                        i++;
                    }
                    temp = ft_calloc(len_count + 1,sizeof(char *));
                    ft_strlcpy(temp,file_check + (i - len_count), len_count + 1);
                    if(!temp)
                        return (0);
                    parse->rgb[6 - rgb_row][rgb_column] = ft_atoi(temp);
                    if(parse->rgb[6 - rgb_row][rgb_column] > 255)
                    {
                        free(temp);
                        return (0);
                    }
                    if(rgb_column == 3)
                        break;
                    rgb_column++;
                    i += len_count;
                    while(file_check[++i] == ' ' && file_check[i] == ',');
                }
            }
        }
        file_check = get_next_line(file);
    }
    close(file);
    return 1;
}
