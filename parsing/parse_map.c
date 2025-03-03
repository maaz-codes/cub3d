#include "../cub3d.h"


int valid_player(char **map, int row, int i, t_parsing *parse)
{   
    (void)map;
    (void)row;
    (void)i;
    (void)parse;
    return (1);
}

int check_direction(char player)
{
    if(player == 'N' || player == 'S'||
    player == 'E' || player == 'W')
        return (1);
    else
        return (0);
}

int valid_nsew(char **map, int row, int i)
{   
    int check;

    check = 0;
    if(map[row - 1][i] == '1' || map[row - 1][i] == '0' ||
        check_direction(map[row - 1][i]))
        check++;
    if(map[row + 1][i] == '1' || map[row + 1][i] == '0' ||
        check_direction(map[row + 1][i]))
        check++;
    if(map[row][i + 1] == '1' || map[row][i + 1] == '0' ||
        check_direction(map[row][i + 1]))
        check++;
    if(map[row][i - 1] == '1' || map[row][i - 1] == '0' ||
        check_direction(map[row][i - 1]))
        check++;
    // printf("check val: %d\n",check);
    if(check == 4)
        return (1);
    return (0);

}
int zero_check(char **map, int row, int i)
{   
    if(i == 0 || map[row][i + 1] == '\0' || i > ft_strlen(map[row - 1]) ||
        i > ft_strlen(map[row + 1]))
    {
        printf("error one\n");
        return (0);
    }
    if(map[row][i + 1] == ' ' || map[row][i - 1] == ' ')
    {
        printf("error two\n");
        return (0);
    }
    if(valid_nsew(map, row, i))
        return (1);
    return (0);
}

int only_spaces(char *map)
{   
    int i;

    i = 0;
    while(map[i] != '\n')
    {
        if(map[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int one_check(char **map, int row, int i)
{   
    if(map[row][i] == '1')
    {   
        if(ft_strlen(map[row - 1]) == 1 || ft_strlen(map[row + 1]) == 1 ||
            only_spaces(map[row - 1]) || only_spaces(map[row + 1]))
        {
            printf("enter error\n");
            return (0);
        }
        return (1);
    }
    return (1);
}

int checkpoint(char **map, int row, int i, t_parsing *parse)
{
    while(map[row][i])
    {   
        // printf("map char: %c\n",map[row][i]);
        if(map[row][i] == '1' || map[row][i] == ' ')
        {
            if(!one_check(map, row, i))
                return (0);
            i++;
        }
        else
        {   
            if(map[row][i] == '\n')
                break;
            else if(map[row][i] == '0')
            {   
                if(!zero_check(map,row,i))
                    return (0);
            }
            else if(check_direction(map[row][i]))
            {
                if(!valid_player(map,row,i,parse))
                    return (0);
            }
            else
                return (0);
            i++;
        }
    }
    return (1);
}

int last_row(t_parsing *parse)
{
    int row;
    int i;

    row = parse->map_length - 1;
    while(row > 0)
    {   
        i = -1;
        while(parse->map[row][i] != '\n')
        {   
            while(parse->map[row][++i] == ' ');
            if(check_which_texture(parse->map[row],i) == 7)
                return (row);
        }
        row--;
    }
    return (0);
}

int check_top_down(char **map,int last_row)
{   
    int i;
    i = 0;
    while(map[0][i] && map[0][i] != '\n')
    {   
        if(map[0][i] != '1' && map[0][i] != ' ')
            return (0);
        i++;
    }
    i = 0;
    while(map[last_row][i] && map[last_row][i] != '\n')
    {
        if(map[last_row][i] != '1' && map[last_row][i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int check_bottom(t_parsing *parse)
{
    int i;
    int row;
    char **map;

    map = parse->map;
    row = -1;
    while(++row < parse->map_length)
    {
        i = -1;
        while(++i < ft_strlen(map[row]) && map[row][i] == '\n')
        {   
            if(map[row][i] != '1' || map[row][i] != ' ' || 
            map[row][i] != '0' || map[row][i] != 'N' || map[row][i] != 'S' ||
            map[row][i] != 'E' || map[row][i] != 'W')
                return(0);
        }
    }
    return(1);
}

int parse_map(t_parsing *parse)
{   
    int i;
    int row;
    char **map;

    map = parse->map;
    row = -1;
    if(!check_top_down(map,last_row(parse)) || !check_bottom(parse))
    {
        printf("first error\n");
        return (0);
    }
    printf("\nparse map area\n");
    while(++row < parse->map_length)
    {   
        i = -1;
        printf("row num: %d\n",row);
        while(i < ft_strlen(map[row]))
        {   
            if(row == 0)
                break;
            else if(row == last_row(parse))
            {
                printf("final index: %d\n",row);
                return (1);
            }
            while(map[row][++i] == ' ');
            if(check_which_texture(map[row],i) == 7)
            {   
                if(!checkpoint(map,row,i,parse))
                    return (0);
                break;
            }
            else if(map[row][i] == '\n')
                break;
            else
                return (0);
        }
    }
    return(1);
}
