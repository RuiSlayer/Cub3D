/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 21:52:29 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/26 22:11:16 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calculate_wall_x(t_cub *cub, t_ray *ray)
{
	double wall_x;

	if (ray->side == SIDE_X)
		wall_x = cub->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = cub->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
int	calculate_texture_x(t_ray *ray, t_img *texture, double wall_x)
{
	int	texture_x;

	texture_x = (int)(wall_x * texture->width);
	if (ray->side == SIDE_X && ray->dir.x > 0)
		texture_x = texture->width - texture_x - 1;
	if (ray->side == SIDE_Y && ray->dir.y < 0)
		texture_x = texture->width - texture_x - 1;
	return(texture_x);
}
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr
		+ (y * texture->line_len)
		+ (x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	shade_color(int color)
{
	return ((color >> 1) & 0x7F7F7F);
}
