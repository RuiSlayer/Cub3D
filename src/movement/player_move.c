/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 05:10:34 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/21 16:55:23 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	try_move(t_cub *cub, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos.x + move_x;
	new_y = cub->player.pos.y + move_y;
	if (!is_wall_or_void(&cub->map, (int)new_x,
			(int)cub->player.pos.y))
		cub->player.pos.x = new_x;
	if (!is_wall_or_void(&cub->map, (int)cub->player.pos.x,
			(int)new_y))
		cub->player.pos.y = new_y;
}

void	move_forward(t_cub *cub)
{
	try_move(cub, cub->player.dir.x * cub->player.move_speed,
		cub->player.dir.y * cub->player.move_speed);
}

void	move_backward(t_cub *cub)
{
	try_move(cub, -cub->player.dir.x * cub->player.move_speed,
		-cub->player.dir.y * cub->player.move_speed);
}

void	move_left(t_cub *cub)
{
	try_move(cub, -cub->player.plane.x * cub->player.move_speed,
		-cub->player.plane.y * cub->player.move_speed);
}

void	move_right(t_cub *cub)
{
	try_move(cub, cub->player.plane.x * cub->player.move_speed,
		cub->player.plane.y * cub->player.move_speed);
}