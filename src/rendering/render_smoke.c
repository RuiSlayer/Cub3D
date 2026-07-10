#include "../inc/cub3d.h"

void	render_smoke_frame(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				color = 0x87CEEB;      // sky blue
			else
				color = 0x555555;      // gray floor

			put_pixel(&cub->mlx.frame, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(
		cub->mlx.ptr,
		cub->mlx.win,
		cub->mlx.frame.img,
		0,
		0);
}
