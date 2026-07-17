#include "../../inc/cub3d.h"

int	close_game(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
    if (keycode == KEY_W)
        cub->input.w = 1;
    else if (keycode == KEY_S)
        cub->input.s = 1;
    else if (keycode == KEY_A)
        cub->input.a = 1;
    else if (keycode == KEY_D)
        cub->input.d = 1;
    else if (keycode == KEY_LEFT)
        cub->input.left = 1;
    else if (keycode == KEY_RIGHT)
        cub->input.right = 1;
	else if (keycode == KEY_ESC)
		close_game(cub);
	return (0);
}

int	handle_keyrelease(int keysym, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
    if (keysym == KEY_W)
        cub->input.w = 0;
    else if (keysym == KEY_S)
        cub->input.s = 0;
    else if (keysym == KEY_A)
        cub->input.a = 0;
    else if (keysym == KEY_D)
        cub->input.d = 0;
    else if (keysym == KEY_LEFT)
        cub->input.left = 0;
    else if (keysym == KEY_RIGHT)
        cub->input.right = 0;
	return (0);
}

void	setup_hooks(t_cub *cub)
{
mlx_hook(cub->mlx.win, EVENT_KEY_PRESS, MASK_KEY_PRESS,
	handle_keypress, cub);
mlx_hook(cub->mlx.win, EVENT_KEY_RELEASE, MASK_KEY_RELEASE,
	handle_keyrelease, cub);
mlx_hook(cub->mlx.win, EVENT_DESTROY, MASK_STRUCTURE,
	close_game, cub);
mlx_loop_hook(cub->mlx.mlx, game_loop, cub);
}
