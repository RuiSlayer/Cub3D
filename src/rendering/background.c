/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:33:39 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 00:41:40 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				color = cub->config.ceiling_color;
			else
				color = cub->config.floor_color;
			put_pixel(&cub->mlx.frame, x, y, color);
			x++;
		}
		y++;
	}
}
