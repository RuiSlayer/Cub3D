/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:32:53 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 00:57:38 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_ray(t_cub *cub, t_ray *ray, int x)
{
    ray->camera_x = 2.0 * x / WIN_WIDTH -1;
    ray->dir.x = cub->player.dir.x
        + cub->player.plane.x * ray->camera_x;
    ray->dir.y = cub->player.dir.y
        + cub->player.plane.y * ray->camera_x;
    ray->map.x = (int)cub->player.pos.x;
    ray->map.y = (int)cub->player.pos.y;
    if (ray->dir.x == 0)
        ray->delta_dist.x = 8e30;
    else
        ray->delta_dist.x = abs(1/ray->dir.x);
    if (ray->dir.y == 0)
        ray->delta_dist.y = 8e30;
    else
        ray->delta_dist.y = abs(1/ray->dir.y);
}

void	calculate_wall_projection(t_ray *ray, t_render *render);