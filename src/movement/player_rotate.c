/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 05:48:44 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 06:38:06 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	rotate_player(t_cub *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(angle)
		- cub->player.dir.y * sin(angle);
	cub->player.dir.y = old_dir_x * sin(angle)
		+ cub->player.dir.y * cos(angle);
	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cos(angle)
		- cub->player.plane.y * sin(angle);
	cub->player.plane.y = old_plane_x * sin(angle)
		+ cub->player.plane.y * cos(angle);
}
