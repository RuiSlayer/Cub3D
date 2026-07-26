/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 05:49:37 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/27 00:00:18 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	update_player(t_cub *cub)
{
	if (cub->input.w)
		move_forward(cub);
	if (cub->input.s)
		move_backward(cub);
	if (cub->input.a)
		move_left(cub);
	if (cub->input.d)
		move_right(cub);
	if (cub->input.left)
		rotate_player(cub, -cub->player.rot_speed);
	if (cub->input.right)
		rotate_player(cub, cub->player.rot_speed);
}

int	game_loop(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	update_player(cub);
	render_frame(cub);
	return (0);
}
