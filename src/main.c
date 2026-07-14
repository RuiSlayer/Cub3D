#include "../inc/cub3d.h"

int main(int argc, char const **argv)
{
	t_cub	cub;

	init_cub(&cub);
	load_map(argv[1], &cub);
	if (init_mlx(&cub))
	{
		free_cub(&cub);
		return (1);
	}
	render_smoke_frame(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx->ptr);
	free_cub(&cub);
	return (0);
}
