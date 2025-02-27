#include "../cub3d.h"

void error_msg(char *str)
{
    printf("%s\n",str);
}

void check_valid_values(char *file_check, int i, t_parsing *parse)
{   
    if(file_check[i] == 'N' && file_check[i + 1] == 'O')
        parse->check_valid[0][0] += 1;
    else if(file_check[i] == 'S' && file_check[i + 1] == 'O')
        parse->check_valid[1][0] += 1;
    else if(file_check[i] == 'W' && file_check[i + 1] == 'E')
        parse->check_valid[2][0] += 1;
    else if(file_check[i] == 'E' && file_check[i + 1] == 'A')
        parse->check_valid[3][0] += 1;
    else if(file_check[i] == 'F')
        parse->check_valid[4][0] += 1;
    else if(file_check[i] == 'C')
        parse->check_valid[5][0] += 1;
}

int is_valid(t_parsing *parse)
{
    int i;
    int check;

    i = -1;
    check = 0;
    while(++i < 6)
    {
        if(parse->check_valid[i][0] == 1)
            check++;
    }
    if(check == 6)
        return 1;
    else
        return 0;
}

int init_parsing(t_parsing **parse)
{   
    int i;
    *parse = malloc(sizeof(t_parsing));
    if(!(*parse))
        return 0;
    (*parse)->check_valid = malloc(6 * sizeof(int *));
    if(!(*parse)->check_valid)
        return 0;
    i = -1;
    while(++i < 6)
    {
        (*parse)->check_valid[i] = malloc(1 * sizeof(int));
        if(!(*parse)->check_valid[i])
            return 0;
        *(*parse)->check_valid[i] = 0;
    }
    return 1;
}

int main(int ac, char **av)
{   
    int file;
    char *file_check;
    int i;
    int valid;
    int rgb_check;
    t_parsing *parse;

    if(!init_parsing(&parse))
        return 0;

    if(ac == 2)
    {   
        valid = 0;
        file = open(av[1],O_RDONLY);
        if(file == -1)
            error_msg("Invalid file\n");
        file_check = get_next_line(file);
        while(file_check)
        {   
            i = -1;
            printf("%s",file_check);
            while(++i < ft_strlen(file_check))
            {   
                if(file_check[i] == ' ')
                    continue;
                else if((file_check[i] == 'N' && file_check[i + 1] == 'O') || 
                (file_check[i] == 'S' && file_check[i + 1] == 'O') || 
                (file_check[i] == 'W' && file_check[i + 1] == 'E') ||
                (file_check[i] == 'E' && file_check[i + 1] == 'A'))
                {   
                    check_valid_values(file_check, i, parse);
                    i += 1;
                    while(file_check[++i] == ' ' && file_check[i] != '\0');
                    if(i != ft_strlen(file_check) - 1)
                        valid++;
                }
                else if(file_check[i] == 'F' || file_check[i] == 'C')
                {   
                    check_valid_values(file_check, i, parse);
                    i += 1;
                    rgb_check = 0;
                    while(file_check[++i])
                    {   
                        if(rgb_check == 2)
                        {   
                            while(file_check[++i] == ' ' && file_check[i])
                            if(!file_check[i])
                                break;
                            while(file_check[++i])
                            {
                                if(file_check[i] >= '0' && file_check[i] <= '9')
                                    continue;
                                else
                                    break;
                            }
                            while(file_check[i] == ' ' && file_check[i])
                                i++;
                            if(file_check[i] == '\n')
                                rgb_check++;
                            else
                                break;
                        }
                        else if(file_check[i] == ' ')
                            continue;
                        else if(file_check[i] >= '0' && file_check[i] <= '9')
                        {   
                            while(file_check[i] >= '0' && file_check[i] <= '9')
                                i++;
                            while(file_check[i] == ' ' && file_check[i])
                                i++;
                            if(file_check[i] == ',')
                                rgb_check++;
                            else
                                break;
                        }
                        else
                            break;
                    }
                    if(rgb_check == 3)
                        valid++;
                }
                else
                    break;
            }
            file_check = get_next_line(file);
        }
        printf("\ncontent: %d\n",valid);
        printf("valid rgb: %d\n",rgb_check);
        for(int check = 0; check < 6; check++)
        {
            printf("value: %d\n",parse->check_valid[check][0]);
        }
        if(is_valid(parse))
            printf("VALUES VALID\n");
        else
            printf("VALUES ERROR\n");
    }
    else
        error_msg("Invalid Args");
    return 0;
}
