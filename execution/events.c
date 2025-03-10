#include "../cub3d.h"

int	handle_key_event(int keycode, t_cub *cub)
{
    double move_x;
    double move_y;

    move_x = 0;
    move_y = 0;
    if (keycode == KEY_W || keycode == KEY_A || 
        keycode == KEY_S || keycode == KEY_D)
    {
        motion(&move_x, &move_y, keycode, cub);
    }
    else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
        rotation(keycode, cub);
    else if (keycode == KEY_ESC)
    {
        cub_slayer(cub);
        exit(EXIT_SUCCESS);
    }
    cub_motion(move_x, move_y, cub);
    return (1);
}

int handle_closing(t_cub *cub)
{
    cub_slayer(cub);
    exit(EXIT_SUCCESS);
}
