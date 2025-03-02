#include "../cub3d.h"

int check_which_texture(char *file_check, int i)
{
    if((file_check[i] == 'N' && file_check[i + 1] == 'O'))
        return 1;
    else if ((file_check[i] == 'S' && file_check[i + 1] == 'O'))
        return 2;
    else if ((file_check[i] == 'W' && file_check[i + 1] == 'E'))
        return 3;
    else if ((file_check[i] == 'E' && file_check[i + 1] == 'A'))
        return 4;
    else if(file_check[i] == 'F' && file_check[i + 1] == ' ')
        return 5;
    else if(file_check[i] == 'C' && file_check[i + 1] == ' ')
        return 6;
    else if((file_check[i] == '1' && file_check[i + 1] == '0') || 
        (file_check[i] == '1' && file_check[i + 1] == '1') || 
        (file_check[i] == '1' && file_check[i + 1] == 'N') ||
        (file_check[i] == '1' && file_check[i + 1] == 'S') ||
        (file_check[i] == '1' && file_check[i + 1] == 'E') ||
        (file_check[i] == '1' && file_check[i + 1] == 'W') ||
        (file_check[i] == '1' && file_check[i + 1] == ' '))
        return 7;
    else
        return 0;
}

int check_if_fc(char *file_check, int i)
{
    if(file_check[i] == 'F' || file_check[i] == 'C')
    {
        if(file_check[i + 1] != ' ')
            return (0);
    }
    else
        if(file_check[i + 2] != ' ')
            return (0);
    return(1);
}

int texture_loop(char *file_check, int *i, t_parsing *parse, int *valid)
{
    int which_texture;

    which_texture = check_which_texture(file_check, (*i));
    if(!check_if_fc(file_check, (*i)))
        return (0);
    check_valid_values(file_check, (*i), parse, "texture");
    while(file_check[(*i)] == ' ' && file_check[(*i)] != '\0')
        (*i) += 1;
    if((*i) != ft_strlen(file_check) - 1 && which_texture < 5)
        (*valid) += 1;
    while(file_check[(*i)])
        (*i) += 1;
    return (1);
}

int check_txt(t_parsing *parse, int *valid)
{
    int i;
    int row;
    char **file_data;
    row = 0;
    file_data = parse->file_data;
    
    while(row < parse->row)
    {
        i = -1;
        while(++i < ft_strlen(file_data[row]))
        {
            while(file_data[row][i] == ' ')
                i++;
            if(check_which_texture(file_data[row],i) && check_which_texture(file_data[row],i) != 0)
            {   
                if(check_which_texture(file_data[row],i) < 5)
                {
                    check_valid_values(file_data[row],i,parse,"texture");
                    while(file_data[row][i] == ' ' && file_data[row][i])
                        i++;
                    if(i != ft_strlen(file_data[row]) - 1)
                        (*valid) += 1;
                    else
                        return (0);
                    break;
                }
                else if(check_which_texture(file_data[row],i) >= 5 
                && check_which_texture(file_data[row],i) <= 7)
                    break;
            }
            else if(file_data[row][i] == '\n')
                break;
            else
                return (0);
        }
        row++;
    }
    return(1);
    
}

int check_texture(t_parsing *parse, int file, int *valid)
{
    int i;
    char *file_check;

    file_check = get_next_line(file);
    while(file_check)
    {
        i = -1;
        while(i < ft_strlen(file_check))
        {
            while(file_check[++i] == ' ');
            if(file_check[i] == '\n')
                break;
            if(check_which_texture(file_check, i))
            {
                if(!texture_loop(file_check, &i, parse, &(*valid)))
                    return (0);
            }
            else
                return (0);
        }
        free(file_check);
        file_check = get_next_line(file);
    }
    close(file);
    return (1);
}
