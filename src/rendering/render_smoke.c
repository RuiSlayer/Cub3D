#include "../../inc/cub3d.h"

void	draw_background(t_cub *cub)
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
				color = 0x87CEEB;
			else
				color = 0x555555;
			put_pixel(&cub->mlx->frame, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(
	t_img *img,
	int x,
	int start,
	int end,
	int color)
{
	int	y;

	if (start < 0)
		start = 0;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;

	y = start;
	while (y <= end)
	{
		put_pixel(img, x, y, color);
		y++;
	}
}

void	render_wall_columns(t_cub *cub)
{
	int	x;
	int	start;
	int	end;

	x = WIN_WIDTH / 2;

	start = WIN_HEIGHT / 4;
	end = WIN_HEIGHT * 3 / 4;

	draw_vertical_line(
		&cub->mlx->frame,
		x,
		start,
		end,
		0xFFFFFF);
}

void	render_frame(t_cub *cub)
{

    draw_background(cub);
    render_wall_columns(cub);
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win,
		cub->mlx->frame.img, 0, 0);
}
