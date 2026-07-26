/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:33:36 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/26 22:10:40 by fgameiro         ###   ########.fr       */
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
	draw_textured_wall(cub, &ray, &render, x);
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
