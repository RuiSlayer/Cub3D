/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:33:36 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/22 23:43:18 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cast_ray_for_column(t_cub *cub, int x)
{
	t_ray		ray;
	t_render	render;

	init_ray(cub, &ray, x);
	init_dda(cub, &ray);
	perform_dda(cub, &ray);
	calculate_wall_projection(&ray, &render);
	draw_wall_column(cub, &ray, &render, x);
}

void	render_wall_columns(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray_for_column(cub, x);
		x++;
	}
}

void	draw_wall_column(t_cub *cub, t_ray *ray, t_render *render, int x)
{
	int	color;
	int	y;

	color = 0xFFFFFF;
	if (ray->side == SIDE_Y)
		color = 0xAAAAAA;
	y = render->draw_start;
	while (y <= render->draw_end)
	{
		put_pixel(&cub->mlx.frame, x, y, color);
		y++;
	}
}
