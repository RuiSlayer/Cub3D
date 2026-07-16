#include "../inc/cub3d.h"

int main(int argc, char const **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_dprintf(2, "Error\nA map should be pass as argument\n"));
	init_cub(&cub);
	if (init_mlx(&cub))
		return (free_cub(&cub), 1);
	load_map(argv[1], &cub);
	render_frame(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx.mlx);
	free_cub(&cub);
	return (0);
}
