#include "../cub3d.h"

void perform_dda(t_cub *cub, t_parsing *parse)
{
    int hit;

    hit = 0;
    while(hit == 0)
    {
        if(cub->sideDistX < cub->sideDistY)
        {
            cub->sideDistX += cub->deltaDistX;
            cub->mapX += cub->stepX;
            cub->side = 0;
        }
        else
        {
            cub->sideDistY += cub->deltaDistY;
            cub->mapY += cub->stepY;
            cub->side = 1;
        }
        if (cub->mapX < 0 || cub->mapY < 0 || cub->mapY >= parse->map_length
			|| cub->mapX >= (int)ft_strlen(parse->map[cub->mapY]))
        	hit = 1;
        else if (cub->map[cub->mapY][cub->mapX] == '1')
            hit = 1;
    }
}

void init_rays(int x, t_cub *cub)
{
    cub->cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
    cub->rayDirX = cub->dirX + cub->planeX * cub->cameraX;
    cub->rayDirY = cub->dirY + cub->planeY * cub->cameraX;
    cub->mapX = (int)cub->posX;
    cub->mapY = (int)cub->posY; 
    if (cub->rayDirX == 0)
        cub->deltaDistX = 1e30;
    else
        cub->deltaDistX = fabs(1 / cub->rayDirX);
    if (cub->rayDirY == 0)
        cub->deltaDistY = 1e30;
    else
        cub->deltaDistY = fabs(1 / cub->rayDirY);
}

void perform_ray_casting(int x, t_cub *cub)
{
    init_rays(x, cub);
    if(cub->rayDirX < 0)
    {
        cub->stepX = -1;
        cub->sideDistX = (cub->posX - cub->mapX) * cub->deltaDistX;
    }
    else
    {
        cub->stepX = 1;
        cub->sideDistX = (cub->mapX + 1.0 - cub->posX) * cub->deltaDistX;
    }
    if(cub->rayDirY < 0)
    {
        cub->stepY = -1;
        cub->sideDistY = (cub->posY - cub->mapY) * cub->deltaDistY;
    }
    else
    {
        cub->stepY = 1;
        cub->sideDistY = (cub->mapY + 1.0 - cub->posY) * cub->deltaDistY;
    }
}

void init_direction(t_cub *cub, int direc)
{
    cub->dirX = 0;
    cub->dirY = 0;
    cub->planeX = 0;
    cub->planeY = 0;
    if (direc == 'N')
    {
        cub->dirY = -1;
        cub->planeX = 0.66;
    }
    else if (direc == 'S')
    {
        cub->dirY = 1;
        cub->planeX = -0.66;
    }
    else if (direc == 'E')
    {
        cub->dirX = 1;
        cub->planeY = 0.66;
    }
    else if (direc == 'W')
    {
        cub->dirX = -1;
        cub->planeY = 0.66;
    }
}
