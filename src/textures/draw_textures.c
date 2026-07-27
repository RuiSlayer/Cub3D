/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 21:54:05 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/27 01:16:16 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_texture_draw(t_render *render, t_img *texture)
{
	render->step = (double)texture->height / render->line_height;
	render->tex_pos = (render->draw_start - WIN_HEIGHT / 2
			+ render->line_height / 2) * render->step;
}

static void	draw_texture_pixels(t_cub *cub, t_render *render,
	t_img *texture, int screen_x)
{
	int		y;
	int		tex_y;
	int		color;

	y = render->draw_start;
	while (y <= render->draw_end)
	{
		tex_y = (int)render->tex_pos;
		render->tex_pos += render->step;
		color = get_texture_pixel(texture, render->texture_x, tex_y);
		if (render->shade)
			color = shade_color(color);
		put_pixel(&cub->mlx.frame, screen_x, y, color);
		y++;
	}
}

void	draw_textured_wall(t_cub *cub, t_ray *ray,
		t_render *render, int screen_x)
{
	t_img	*texture;
	double	wall_x;

	texture = get_wall_texture(cub, ray);
	wall_x = calculate_wall_x(cub, ray);
	render->texture_x = calculate_texture_x(ray, texture, wall_x);
	render->shade = (ray->side == SIDE_Y);
	init_texture_draw(render, texture);
	draw_texture_pixels(cub, render, texture, screen_x);
}
