/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_collumn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:33:36 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 00:42:55 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

void	cast_ray_for_column(t_cub *cub, int x);
/* cast_ray_for_column(cub, x)
    declare t_ray ray
    declare t_render render

    init_ray(cub, &ray, x)
    init_dda(cub, &ray)
    perform_dda(cub, &ray)
    calculate_wall_projection(&ray, &render)
    draw_wall_column(cub, &ray, &render, x) */

void	render_wall_columns(t_cub *cub)
{
	int	x;
	int	start;
	int	end;

	x = WIN_WIDTH / 2;

	start = WIN_HEIGHT / 4;
	end = WIN_HEIGHT * 3 / 4;

	draw_vertical_line(
		&cub->mlx.frame,
		x,
		start,
		end,
		0xFFFFFF);
}
