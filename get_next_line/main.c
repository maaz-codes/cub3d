// #include "get_next_line.h"
#include "../cub3d.h"

int main()
{
    int fd = open("example.txt", O_RDONLY);
    char *char_lines;
    int lines = 1;
    while((char_lines = get_next_line(fd)))
        printf("%d: %s\n", lines++, char_lines);
}