#include "../cub3d.h"

int get_location(char **file_data)
{
    int row;
    int len;

    row = 0;
    while(file_data[row])
    {   
        len = 0;
        while(file_data[row][len])
        {   
            while(file_data[row][len] == ' ')
                len++;
            if(check_which_texture(file_data[row],len) == 7)
                return (row + 1);
            len++;
        }
        row++;
    }
    return (0);
}
int get_map(t_parsing *parse)
{   
    (void)parse;
    // int start;

    // start = get_location(parse->file_data);
    // printf("row length %d\n",parse->row);

    
    return (1);
}