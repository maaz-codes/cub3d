#include "../cub3d.h"

int last_rgb(char *file_check, int *i, int *rgb_check)
{   
    (*i) += 1;
    while(file_check[*i] == ' ' && file_check[*i])
        (*i) += 1;
    if(!file_check[(*i)])
        return (0);
    while(file_check[*i])
    {
        if(file_check[(*i)] >= '0' && file_check[(*i)] <= '9')
        {
            (*i) += 1;
            continue;
        }
        else
            break;
    }
    while(file_check[(*i)] == ' ' && file_check[(*i)])
        (*i) += 1;
    if(file_check[(*i)] == '\n')
    {   
        (*rgb_check) += 1;
        return (1);    
    }
    else
        return (0);
}

int one_and_two_rgb(char *file_check, int *i, int *rgb_check)
{   
    while(file_check[*i])
    {
        if(file_check[*i] >= '0' && file_check[*i] <= '9')
        {
            (*i) += 1;
            continue;
        }
        else
            break;
    }
    while(file_check[(*i)] == ' ' && file_check[(*i)])
        (*i) += 1;
    if(file_check[(*i)] == ',' && (file_check[(*i) + 1] == ' ' 
    || (file_check[(*i)] >= '0' && file_check[(*i)] <= '9')))
    {   
        (*rgb_check) += 1;
        return (1);
    }
    else
        return (0);
}
int check_rgb(t_parsing *parse, int file, int *valid)
{
    int i;
    (void)valid;
    char *file_check;
    int rgb_check;

    file_check = get_next_line(file);
    while(file_check)
    {   
        i = -1;
        while(++i < ft_strlen(file_check))
        {
            rgb_check = 0;
            if(file_check[i] == 'F' || file_check[i] == 'C')
            {   
                check_valid_values(file_check, i, parse, "rgb");
                while(file_check[++i])
                {   
                    if(rgb_check == 2)
                    {
                        if(!last_rgb(file_check, &i, &rgb_check))
                            break;
                    }
                    else if(file_check[i] == ' ')
                        continue;
                    else if(file_check[i] >= '0' && file_check[i] <= '9')
                    {   
                        if(!one_and_two_rgb(file_check, &i, &rgb_check))
                            break;
                    }
                    else
                        break;
                }
                if(rgb_check == 3)
                    (*valid) += 1;
                else
                    return (0);
            }
        }
        file_check = get_next_line(file);
    }
    close(file);
    return (1);
}
