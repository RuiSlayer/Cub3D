/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 19:24:19 by slayer            #+#    #+#             */
/*   Updated: 2026/07/23 19:35:23 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while (map->grid[y])
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->spawn_dir = '\0';
}

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < DIRECTION_COUNT)
	{
		if (config->texture_path[i])
			free(config->texture_path[i]);
		config->texture_path[i] = NULL;
		i++;
	}
}

void	free_textures(t_mlx *mlx, t_textures *textures)
{
	int	i;

	i = 0;
	while (i < DIRECTION_COUNT)
	{
		if (textures->wall[i].img && mlx->mlx)
			mlx_destroy_image(mlx->mlx, textures->wall[i].img);
		textures->wall[i].img = NULL;
		i++;
	}
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->frame.img && mlx->mlx)
	{
		mlx_destroy_image(mlx->mlx, mlx->frame.img);
		mlx->frame.img = NULL;
	}
	if (mlx->win && mlx->mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	if (mlx->mlx)
	{
# if defined(__linux__)
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
# endif
		mlx->mlx = NULL;
	}
}

void	free_cub(t_cub *cub)
{
	free_map(&cub->map);
	free_config(&cub->config);
	free_textures(&cub->mlx, &cub->textures);
	free_mlx(&cub->mlx);
}
