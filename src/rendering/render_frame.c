/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:32:05 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/17 01:59:38 by fgameiro         ###   ########.fr       */
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
