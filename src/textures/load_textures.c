/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 19:06:10 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/23 19:17:27 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int load_texture(void *mlx, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, 
		&tex->width, &tex->height);
	if(!tex->img)
		return(FAILURE);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, 
		&tex->line_len, &tex->endian);
	return(SUCCESS);
}

int load_all_textures(t_cub *cub)
{
	if (load_texture(cub->mlx.mlx,
		&cub->textures.wall[NO],
		cub->config.texture_path[NO]))
		return (FAILURE);
	if (load_texture(cub->mlx.mlx,
		&cub->textures.wall[SO],
		cub->config.texture_path[SO]))
		return (FAILURE);
	if (load_texture(cub->mlx.mlx,
		&cub->textures.wall[EA],
		cub->config.texture_path[EA]))
		return (FAILURE);
	if (load_texture(cub->mlx.mlx,
		&cub->textures.wall[WE],
		cub->config.texture_path[WE]))
		return (FAILURE);
	return(SUCCESS);
}