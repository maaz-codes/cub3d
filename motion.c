#include "cub3d.h"

void cub_motion(double move_x, double move_y, t_cub *cub)
{
    // bound check
    if (move_x >= 0 && move_x < mapWidth && move_y >= 0 && move_y < mapHeight)
        if (cub->map[(int)move_x][(int)move_y] == WALKABLE)
        {
            printf("WALKing: mx:%f | my:%f\n", move_x, move_y);
            cub->posX = move_x;
            cub->posY = move_y;
        }
    // cub_rendering(cub);
}

void rotation(int dir, t_cub *cub)
{
    double rot;
    double old_dir_x;
    double old_plane_x;
    double cos_rot;
    double sin_rot;
    
    if (dir == KEY_MINUS)
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
    if (dir == KEY_UP)
    {
        *mx = cub->posX + (cub->dirX * MOVE_SPEED);
        *my = cub->posY;
    }
    else if (dir == KEY_DOWN)
    {
        *mx = cub->posX - (cub->dirX * MOVE_SPEED);
        *my = cub->posY;
    }
    else if (dir == KEY_LEFT)
    {
        *mx = cub->posX;
        *my = cub->posY + (cub->dirY * MOVE_SPEED);
    }
    else if (dir == KEY_RIGHT)
    {
        *mx = cub->posX;
        *my = cub->posY - (cub->dirY * MOVE_SPEED);
    }
}

int	handle_keypress(int keycode, t_cub *cub)
{
    double move_x;
    double move_y;

    if (keycode == KEY_UP || keycode == KEY_DOWN || 
        keycode == KEY_LEFT || keycode == KEY_RIGHT)
    {
        motion(&move_x, &move_y, keycode, cub);
    }
    else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
        rotation(keycode, cub);
    cub_motion(move_x, move_y, cub);
    return (1);
}
