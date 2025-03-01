#include "../cub3d.h"

int set_values_rgb(char *file_check, t_parsing *parse, char *pos,int rgb_pos)
{   
    char **remove_comma;
    char *remove_space;
    char *trim_pos;
    int rgb_num;
    int i;
    
    i = -1;
    trim_pos = ft_strtrim(file_check,pos);
    remove_comma = ft_split(trim_pos,',');
    free(trim_pos);
    while(++i < 3)
    {
        remove_space = ft_strtrim(remove_comma[i]," ");
        rgb_num = ft_atoi(remove_space);
        if(rgb_num > 255 || ft_strlen(remove_space) > 4)
        {
            (free_double(remove_comma, 3),free(remove_space));
            return (0);
        }
        parse->rgb[rgb_pos][i] = rgb_num;
        free(remove_space);
    }
    free_double(remove_comma, 3);
    return (1);
}

int save_rgb(t_parsing *parse, int file)
{
    char *file_check;
    (void)parse;
    int i;

    file_check = get_next_line(file);
    while(file_check)
    {   
        i = -1;
        while(++i < ft_strlen(file_check))
        {   
            if(check_which_texture(file_check, i) == 5)
            {
                if(!set_values_rgb(file_check, parse,"F",0))
                    return (0);
            }
            else if(check_which_texture(file_check, i) == 6)
                if(!set_values_rgb(file_check, parse,"C",1))
                    return (0);
        }
        free(file_check);
        file_check = get_next_line(file);
    }
    close(file);
    return 1;
}
