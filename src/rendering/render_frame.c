/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:32:05 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/21 16:56:32 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_frame(t_cub *cub)
{
	draw_background(cub);
	render_wall_columns(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win,
		cub->mlx.frame.img, 0, 0);
}
