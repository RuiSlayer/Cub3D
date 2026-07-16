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
	if (keycode == KEY_ESC)
		close_game(cub);
	return (0);
}

void	setup_hooks(t_cub *cub)
{
	mlx_key_hook(cub->mlx.win, handle_keypress, cub);
	mlx_hook(cub->mlx.win, 17, 0, close_game, cub);
}
