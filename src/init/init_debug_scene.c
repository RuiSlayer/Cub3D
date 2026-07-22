/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_debug_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 23:26:02 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/22 22:59:58 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_debug_scene(t_cub *cub)
{
	static char	*debug_map[] = {
		"1111111",
		"1000001",
		"1001001",
		"1000001",
		"1000001",
		"1000001",
		"1111111",
		NULL
	};
	int			y;

	cub->map.width = 7;
	cub->map.height = 7;
	cub->map.spawn_dir = 'S';
	cub->map.grid = ft_calloc(cub->map.height + 1, sizeof(char *));
	if (!cub->map.grid)
		return (FAILURE);
	y = 0;
	while (y < cub->map.height)
	{
		cub->map.grid[y] = ft_strdup(debug_map[y]);
		if (!cub->map.grid[y])
		{
			free_map(&cub->map);
			return (FAILURE);
		}
		y++;
	}
	cub->player.pos.x = 3.5;
	cub->player.pos.y = 4.5;
	cub->player.dir.x = 0.0;
	cub->player.dir.y = -1.0;
	cub->player.plane.x = 0.66;
	cub->player.plane.y = 0.0;
	cub->player.move_speed = 0.03;
	cub->player.rot_speed = 0.01;
	cub->config.ceiling_color = 0x87CEEB;
	cub->config.floor_color = 0x444444;
	return (SUCCESS);
}