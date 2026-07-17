/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:33:45 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 02:31:53 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_dda(t_cub *cub, t_ray *ray)
{
    if (ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = 
            (cub->player.pos.x - ray->map.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side =
            (cub->player.pos.x + 1.0 - cub->player.pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = 
            (cub->player.pos.y - ray->map.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->side =
            (cub->player.pos.y + 1.0 - cub->player.pos.y) * ray->delta_dist.y;
    }
}

void	perform_dda(t_cub *cub, t_ray *ray)
{
    while(ray->hit == 0)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map.x += 
        }
}

/* 
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
      }  */