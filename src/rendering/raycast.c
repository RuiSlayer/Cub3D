/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:32:53 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/21 16:52:26 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static double	ft_abs_double(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	init_ray(t_cub *cub, t_ray *ray, int x)
{
    ray->camera_x = 2.0 * x / WIN_WIDTH - 1.0;
    ray->dir.x = cub->player.dir.x
        + cub->player.plane.x * ray->camera_x;
    ray->dir.y = cub->player.dir.y
        + cub->player.plane.y * ray->camera_x;
    ray->map.x = (int)cub->player.pos.x;
    ray->map.y = (int)cub->player.pos.y;
    if (ray->dir.x == 0)
        ray->delta_dist.x = 1e30;
    else
        ray->delta_dist.x = ft_abs_double(1.0 / ray->dir.x);
    if (ray->dir.y == 0)
        ray->delta_dist.y = 1e30;
    else
    {
        ray->delta_dist.y = ft_abs_double(1.0 / ray->dir.y);
        ray->hit = 0;
        ray->side = SIDE_X;
    }
}

void	calculate_wall_projection(t_ray *ray, t_render *render)
{
    if (ray->side == SIDE_X)
        ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
    else
        ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
    if (ray->perp_wall_dist <= 0)
        ray->perp_wall_dist = 0.01;
    render->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
    render->draw_start = -render->line_height / 2 + WIN_HEIGHT / 2;
    render->draw_end = render->line_height / 2 + WIN_HEIGHT / 2;
    if (render->draw_start < 0)
        render->draw_start = 0;
    if (render->draw_end >= WIN_HEIGHT)
        render->draw_end = WIN_HEIGHT - 1;
}
