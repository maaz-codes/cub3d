#include "../cub3d.h"

void error_msg(char *str)
{
    printf("%s\n",str);
}

int main(int ac, char **av)
{   
    int file;
    char *file_check;
    int i;
    int valid;

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
                if((file_check[i] == 'N' && file_check[i + 1] == 'O') || 
                (file_check[i] == 'S' && file_check[i + 1] == 'O') || 
                (file_check[i] == 'W' && file_check[i + 1] == 'E') ||
                (file_check[i] == 'E' && file_check[i + 1] == 'A'))
                {   
                    i += 1;
                    while(file_check[++i] == ' ' && file_check[i] != '\0');
                    if(i == ft_strlen(file_check) - 1)
                        printf("not valid\n");
                    else
                    {
                        printf("enter else\n");
                        valid++;
                        file_check = get_next_line(file);
                    }
                }
                else if(file_check[i] == 'F')
                    valid++;
                else if(file_check[i] == 'C')
                    valid++;
            }
            file_check = get_next_line(file);
        }
        printf("\ncontent: %d\n",valid);
    }
    else
    {
        error_msg("Invalid Args");
    }
    return 1;

}
