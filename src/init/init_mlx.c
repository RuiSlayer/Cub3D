#include "../../inc/cub3d.h"

int	init_cub(t_cub *cub)
{
	int	i;

	i = 0;
	cub->mlx.mlx = malloc(sizeof(t_mlx));
	if (!cub->mlx.mlx)
		return (1);
	ft_bzero(cub, sizeof(t_cub));
	cub->config.ceiling_color = -1;
	cub->config.floor_color = -1;
	while(i < DIRECTION_COUNT)
	{
		cub->config.texture_path[i] = NULL;
		i++;
	}
	return (0);
}

int	init_mlx(t_cub *cub)
{
	cub->mlx.mlx = malloc(sizeof(t_mlx));
	if (!cub->mlx.mlx)
	{
		printf("Malloc failed for mlx\n");
		return (1);
	}
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
	{
		printf("Couldn't initiate MLX :(\n");
		return (1);
	}
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "First test");
	if (!cub->mlx.win)
	{
		printf("Couldn't open MLX window\n");
		return (1);
	}
	cub->mlx.frame.img = mlx_new_image(cub->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->mlx.frame.img)
	{
		printf("Couldn't build frame\n");
		return (1);
	}
	cub->mlx.frame.addr = mlx_get_data_addr(cub->mlx.frame.img,
			&cub->mlx.frame.bpp,
			&cub->mlx.frame.line_len,
			&cub->mlx.frame.endian);
	if (!cub->mlx.frame.addr)
	{
		printf("Couldn't find address\n");
		return (1);
	}
	return (0);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH)
		return ;
	if (y < 0 || y >= WIN_HEIGHT)
		return ;

	dst = img->addr
		+ (y * img->line_len)
		+ (x * (img->bpp / 8));

	*(unsigned int *)dst = color;
}
