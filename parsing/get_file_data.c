#include "../cub3d.h"

void get_rows(t_parsing *parse, int file)
{
    (void)parse;
    char *file_check;
    int  i;
    int  row;

    row = 0;
    file_check = get_next_line(file);
    while(file_check)
    {   
        i = 0;
        if(file_check[i] == '\n')
            row++;
        while(file_check[i])
        {   
            i++;
        }
        free(file_check);
        file_check = get_next_line(file);
    }
    parse->row = row;
    close(file);
}

int get_file_data(t_parsing *parse, int file)
{   
    char *file_check;
    int  row;
    
    row = 0;
    file_check = get_next_line(file);
    while(file_check)
    {
        if(file_check)
        {   
            parse->file_data[row] = ft_strdup(file_check);
            row++;
        }
        free(file_check);
        file_check = get_next_line(file);
    }
    close(file);
    return (0);
}