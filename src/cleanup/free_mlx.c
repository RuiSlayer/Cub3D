#include "../../inc/cub3d.h"

// static void	free_frame(t_cub *cub)
// {
// 	if (cub->mlx.frame.img != NULL && cub->mlx.mlx != NULL)
// 	{
// 		mlx_destroy_image(cub->mlx.mlx, cub->mlx.frame.img);
// 		cub->mlx.frame.img = NULL;
// 		cub->mlx.frame.addr = NULL;
// 	}
// }

// void	free_cub(t_cub *cub)
// {
// 	if (cub == NULL || cub->mlx.mlx == NULL)
// 		return ;
// 	free_frame(cub);
// 	if (cub->mlx.win != NULL && cub->mlx.mlx != NULL)
// 	{
// 		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
// 		cub->mlx.win = NULL;
// 	}
// # if defined(__linux__)
// 	if (cub->mlx.mlx != NULL)
// 	{
// 		mlx_destroy_display(cub->mlx.mlx);
// 		free(cub->mlx.mlx);
// 	}
// # endif
// 	cub->mlx.mlx = NULL;
// 	free(cub->mlx.mlx);
// 	cub->mlx.mlx = NULL;
// }
