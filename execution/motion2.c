#include "../cub3d.h"

void cub_motion(double move_x, double move_y, t_cub *cub)
{
    // bound check
    if (move_x > 1 && move_x < cub->map_ht && move_y > 1 && move_y < cub->map_wd)
    {
        if (cub->map[(int)move_x][(int)cub->posY] == WALKABLE)
            cub->posX = move_x;
        if (cub->map[(int)cub->posX][(int)move_y] == WALKABLE)
            cub->posY = move_y;
    }
}

void rotation(int dir, t_cub *cub)
{
    double rot;
    double old_dir_x;
    double old_plane_x;
    double cos_rot;
    double sin_rot;
    
    if (dir == KEY_RIGHT)
        rot = ROT_SPEED;
    else
        rot = -ROT_SPEED;
    cos_rot = cos(rot);
    sin_rot = sin(rot);
    old_dir_x = cub->dirX;
    cub->dirX = cub->dirX * cos_rot - cub->dirY * sin_rot;
    cub->dirY = old_dir_x * sin_rot + cub->dirY * cos_rot;
    old_plane_x = cub->planeX;
    cub->planeX = cub->planeX * cos_rot - cub->planeY * sin_rot;
    cub->planeY = old_plane_x * sin_rot + cub->planeY * cos_rot;
}

void motion(double *mx, double *my, int dir, t_cub *cub)
{
    if (dir == KEY_W)
    {
        *mx = cub->posX + (cub->dirX * MOVE_SPEED);
        *my = cub->posY + (cub->dirY * MOVE_SPEED);
    }
    else if (dir == KEY_S)
    {
        *mx = cub->posX - (cub->dirX * MOVE_SPEED);
        *my = cub->posY - (cub->dirY * MOVE_SPEED);
    }
    else if (dir == KEY_D)
    {
        *mx = cub->posX + (cub->planeX * MOVE_SPEED);
        *my = cub->posY + (cub->planeY * MOVE_SPEED);
    }
    else if (dir == KEY_A)
    {
        *mx = cub->posX - (cub->planeX * MOVE_SPEED);
        *my = cub->posY - (cub->planeY * MOVE_SPEED);
    }
}
