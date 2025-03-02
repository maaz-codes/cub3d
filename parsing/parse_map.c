#include "../cub3d.h"

int parse_map(t_parsing *parse)
{
    int i;
    int row;
    int check;
    char **map;

    map = parse->map;

    check = 0;
    row = 0;
    while(row < parse->map_length)
    {   
        i = -1;
        while(++i < ft_strlen(map[row]))
        {   
            while(map[row][i] == ' ')
                i++;
            if(check_which_texture(map[row],i) == 7)
            {
                check++;
                break;
            }
            else if(map[row][i] == '\n')
            {
                check++;
                break;
            }
            else
                return (0);
        }
        row++;
    }
    printf("\nmap len: %d\n",parse->map_length);
    printf("\nrow: %d\n",row);
    printf("check: %d\n",check);
    return(1);
    
}