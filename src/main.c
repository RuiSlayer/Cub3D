#include "../inc/cub3d.h"

int main(int argc, char const **argv)
{
	t_cub	cub;

	(void)argv;
	if (argc != 2)
		return (ft_dprintf(2, "Error\nA map should be pass as argument\n"));
	init_cub(&cub);
	if(init_debug_scene(&cub))
		return(free_cub(&cub), 1);
	if (init_mlx(&cub))
		return (free_cub(&cub), 1);
	render_frame(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx.mlx);
	free_cub(&cub);
	return (0);
}
