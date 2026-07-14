#include "../../inc/cub3d.h"

static void	free_frame(t_cub *cub)
{
	if (cub->mlx->frame.img != NULL && cub->mlx->ptr != NULL)
	{
		mlx_destroy_image(cub->mlx->ptr, cub->mlx->frame.img);
		cub->mlx->frame.img = NULL;
		cub->mlx->frame.addr = NULL;
	}
}

void	free_cub(t_cub *cub)
{
	if (cub == NULL || cub->mlx == NULL)
		return ;
	free_frame(cub);
	if (cub->mlx->win != NULL && cub->mlx->ptr != NULL)
	{
		mlx_destroy_window(cub->mlx->ptr, cub->mlx->win);
		cub->mlx->win = NULL;
	}
# if defined(__linux__)
	if (cub->mlx->ptr != NULL)
	{
		mlx_destroy_display(cub->mlx->ptr);
		free(cub->mlx->ptr);
	}
# endif
	cub->mlx->ptr = NULL;
	free(cub->mlx);
	cub->mlx = NULL;
}
