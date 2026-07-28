/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 23:22:03 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/28 02:31:35 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	player_init_direc(t_cub *cub)
{
	if (cub->map.spawn_dir == 'N')
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = -1;
	}
	if (cub->map.spawn_dir == 'S')
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = 1;
	}
	if (cub->map.spawn_dir == 'E')
	{
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
	}
	if (cub->map.spawn_dir == 'W')
	{
		cub->player.dir.x = -1;
		cub->player.dir.y = 0;
	}
}

void	player_init(t_cub *cub)
{
	cub->player.pos.x = cub->map.spawn_pos.x + 0.5;
	cub->player.pos.y = cub->map.spawn_pos.y + 0.5;
	player_init_direc(cub);
	cub->player.plane.x = -cub->player.dir.y * 0.66;
	cub->player.plane.y = cub->player.dir.x * 0.66;
	cub->player.move_speed = 0.004;
	cub->player.rot_speed = 0.002;
}
