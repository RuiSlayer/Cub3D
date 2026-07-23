/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:33:45 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 08:18:06 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_wall_or_void(t_map *map, int x, int y)
{
	if (!map || !map->grid)
		return (1);
	if (x < 0 || y < 0)
		return (1);
	if (x >= map->width || y >= map->height)
		return (1);
	if (!map->grid[y])
		return (1);
	if (map->grid[y][x] == '1')
		return (1);
	if (map->grid[y][x] == ' ')
		return (1);
	return (0);
}

void	init_dda(t_cub *cub, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (cub->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - cub->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (cub->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - cub->player.pos.y)
			* ray->delta_dist.y;
	}
}

void	perform_dda(t_cub *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = SIDE_X;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = SIDE_Y;
		}
		if (is_wall_or_void(&cub->map, ray->map.x, ray->map.y))
			ray->hit = 1;
	}
}
