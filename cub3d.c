#include "cub3d.h"

// MLX_utils
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void cub_init(t_cub *cub)
{
    cub->connection = mlx_init();
    cub->win = mlx_new_window(cub->connection, screenWidth, screenHeight, "cub3D");
    cub->img.img = mlx_new_image(cub->connection, screenWidth, screenHeight);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);

    cub->posX = 12;
    cub->posY = 12;

    cub->dirX = -1;
    cub->dirY = 0;

    cub->planeX = 0;
    cub->planeY = 0.66;
}

void	color_pxl(int x, int y, int color, t_cub *cub)
{
    // printf("x:%d| y:%d\n", x, y);
    my_mlx_pixel_put(&cub->img, x, y, color);
}

void print_map(char **map)
{
    int i = 0;

    while (i < 5)
    {
        int j = 0;
        while (j < 10)
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void draw_strip(int x, int start, int end, int color, t_cub *cub)
{
    // printf("SegFal10\n");
    int ceil;
    int floor;

    ceil = 0;
    floor = end;
    while (ceil < start)
    {
        color_pxl(x, ceil, COLOR_MAGENTA, cub);
        ceil++;
    }
    while (start < end)
    {
        // printf("SegFal11\n");
        color_pxl(x, start, color, cub);
        start++;
    }
    while (floor < screenHeight)
    {
        color_pxl(x, floor, COLOR_PURPLE, cub);
        floor++;
    }
}

unsigned long getTicks(t_cub *cub) 
{
    struct timeval tv;
    struct timeval tick;

    gettimeofday(&tv, NULL);
    tick.tv_sec = tv.tv_sec - cub->start_time.tv_sec;
    tick.tv_usec = tv.tv_usec - cub->start_time.tv_usec;
    return (tick.tv_sec * 1000) + (tick.tv_usec / 1000); // Convert to milliseconds
}

int	handle_key_release(int keycode, t_cub *cub)
{
    //move forward if no wall in front of you
    if (keycode == KEY_UP)
    {
        printf("KEY_UP PRESSED!\n");
        // if(cub->map[(int)(cub->posX + cub->dirX * cub->move_speed)][(int)cub->posY] == WALKABLE) 
            // cub->posX = cub->posX + cub->dirX * cub->move_speed;
        if(cub->map[(int)(cub->posX)][(int)cub->posY] == WALKABLE) 
            cub->posX -= 1;
        // if(cub->map[(int)cub->posX][(int)(cub->posY + cub->dirY * cub->move_speed)] == WALKABLE) 
        //     cub->posY = cub->posY;
    } 
    else if (keycode == KEY_DOWN)
    {
        printf("KEY_DOWN PRESSED!\n");
        if(cub->map[(int)(cub->posX)][(int)cub->posY] == WALKABLE) 
            cub->posX += 1;
    } 
    else if (keycode == KEY_LEFT)
    {
        printf("KEY_LEFT PRESSED!\n");
        // if(cub->map[(int)(cub->posX + cub->dirX * cub->move_speed)][(int)cub->posY] == WALKABLE) 
            // cub->posX = cub->posX + cub->dirX * cub->move_speed;
        if(cub->map[(int)(cub->posX)][(int)cub->posY] == WALKABLE) 
            cub->posY -= 1;
        // if(cub->map[(int)cub->posX][(int)(cub->posY + cub->dirY * cub->move_speed)] == WALKABLE) 
        //     cub->posY = cub->posY;
    } 
    else if (keycode == KEY_RIGHT)
    {
        printf("KEY_RIGHT PRESSED!\n");
        if(cub->map[(int)(cub->posX)][(int)cub->posY] == WALKABLE) 
            cub->posY += 1;
    }
    else if (keycode == KEY_PLUS)
    {
        printf("KEY_PLUS PRESSED!\n");
        if(cub->map[(int)(cub->posX)][(int)cub->posY] == WALKABLE) 
            cub->posY += 1;
    }
    else if (keycode == KEY_MINUS)
    {
        printf("KEY_MINUS PRESSED!\n");
        if(cub->map[(int)(cub->posX)][(int)cub->posY] == WALKABLE) 
            cub->posY -= 1;
    }
    cub_rendering(cub);
    return (1);
}

int cub_rendering(t_cub *cub)
{
    int x = 0;
    int y = 0;
    printf("posX:%f| posY:%f\n", cub->posX, cub->dirY);

    // double posX = 22, posY = 12;  //x and y start position
    // double dirX = -1, dirY = 0; //initial direction vector
    // double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame

    // printf("SegFal1\n");
    while (x < screenWidth)
    {
        //calculate ray position and direction
        double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
        double rayDirX = cub->dirX + cub->planeX * cameraX;
        double rayDirY = cub->dirY + cub->planeY * cameraX;
        //which box of the map we're in
        int mapX = (int)cub->posX;
        int mapY = (int)cub->posY; 

        // printf("SegFal2\n");
        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        // printf("SegFal3\n");
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (cub->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->posX) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (cub->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->posY) * deltaDistY;
        }
        // printf("SegFal4\n");
        //perform DDA
        while(hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            // printf("SegFal5\n");
            if(sideDistX < sideDistY)
            {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
            }
            else
            {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
            }
            // printf("SegFal6\n");
            //Check if ray has hit a wall
            if(cub->map[mapX][mapY] > 0) hit = 1;
        }
        // printf("SegFal7\n");
        if (side == 0) 
            perpWallDist = (sideDistX - deltaDistX);
        else          
            perpWallDist = (sideDistY - deltaDistY);

        //Calculate height of line to draw on screen
        int lineHeight = (int)(screenHeight / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if(drawStart < 0) 
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if(drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        int color;
        // printf("SegFal8\n");
        switch(cub->map[mapX][mapY])
        {
            case 1:  color = COLOR_RED;    break; //red
            case 2:  color = COLOR_GREEN;  break; //green
            case 3:  color = COLOR_BLUE;   break; //blue
            case 4:  color = COLOR_WHITE;  break; //white
            default: color = COLOR_YELLOW; break; //yellow
        }

        //give x and y sides different brightness
        if(side == 1) 
            color = color / 2;
        // printf("SegFal9\n");
        draw_strip(x, drawStart, drawEnd, color, cub);   
        x++;
    }
    // timing for input and FPS counter
    oldTime = time;
    time = getTicks(cub);
    
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    printf("FPS Counter:%f\n", 1.0 / frameTime);
    // print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    cub->move_speed = frameTime * 5.0;
    cub->rot_speed = frameTime * 3.0;
    // readKeys();
    //move forward if no wall in front of you
    // if(keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if(keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if(keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if(keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    // }
    mlx_put_image_to_window(cub->connection, cub->win, cub->img.img, 0, 0);
    return (1);
}

int main(int ac, char **av)
{
    t_cub *cub;
    t_parsing *parse;

    if(ac == 2)
    {
        if(!parse_init_save(av))
            return (0);
        int worldMap[mapWidth][mapHeight]=
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
            {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

        cub = (t_cub *)malloc(1024 * 100);
        cub->map = worldMap;
        
        if (gettimeofday(&cub->start_time, NULL) == 0)
            printf("Started!\n");
        else    
            return (write(2, "Time-function failed:(\n", 24), 1);

        cub_init(cub);
        cub_rendering(cub);
        // mlx_loop_hook(cub->connection, cub_rendering, cub);
        mlx_key_hook(cub->win, handle_key_release, cub);
        mlx_loop(cub->connection);

        mlx_destroy_window(cub->connection, cub->win);
        free(cub->connection);
        free_data(parse);
    }
    else
        printf("Invalid Args\n");
}
