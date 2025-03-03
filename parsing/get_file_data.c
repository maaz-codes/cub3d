#include "../cub3d.h"

void get_rows(t_parsing *parse, int file)
{
    char *file_check;
    int  i;
    int  row;

    row = 0;
    file_check = get_next_line(file);
    while(file_check)
    {   
        i = 0;
        
        while(i < ft_strlen(file_check))
        {   
            if(file_check[i] == '\n')
            {
                row++;
                break;
            }
            else if(file_check[i] != '\n' && file_check[i])
            {
                row++;
                break;
            }
            else if(file_check[i] == '\0')
                break;
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
    int  i;
    int  row;
    
    row = 0;
    file_check = get_next_line(file);
    while(file_check)
    {   
        i = 0;
        while(i < ft_strlen(file_check))
        {
            if(file_check[i] == '\n')
            {   
                parse->file_data[row] = ft_calloc(2,sizeof(char *));
                if(!parse->file_data[row])
                    return(0);
                ft_strlcpy(parse->file_data[row],"\n",2);
                row += 1;
                break;
            }
            else if(file_check[i] != '\n')
            {   
                parse->file_data[row] = ft_calloc(ft_strlen(file_check) + 1,sizeof(char *));
                if(!parse->file_data[row])
                    return(0);
                ft_strlcpy(parse->file_data[row],file_check,ft_strlen(file_check) + 1);
                row += 1;
                break;
            }
            else if(file_check[i] == '\0')
                break;
            i++;
        }
        free(file_check);
        file_check = get_next_line(file);
    }
    close(file);
    return (0);
}
