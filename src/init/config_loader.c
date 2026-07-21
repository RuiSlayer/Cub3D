/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 18:27:48 by slayer            #+#    #+#             */
/*   Updated: 2026/07/21 18:33:57 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	set_texture_path(t_cub *cub, char **split_line)
{
	t_direction	dir;

	if (ft_split_len(split_line) != 2)
		return (-1);
	if (!has_xpm_ext(split_line[1]))
		return (4);
	dir = get_direction(split_line[0]);
	if (dir == DIRECTION_COUNT)
		return (-1);
	if (cub->config.texture_path[dir] != NULL)
		return (9);
	cub->config.texture_path[dir] = ft_strdup(split_line[1]);
	if (!cub->config.texture_path[dir])
		return (-1);
	cub->config.config_count++;
	return (0);
}

static int	is_valid_number(char *str)
{
	int		i;
	long	value;

	if (!str || !str[0])
		return (0);
	i = 0;
	ft_trim_newline(str);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	value = ft_atol(str);
	if (value < 0 || value > 255)
		return (0);
	return (1);
}

static int	rgb2hex(char *rgb)
{
	char	**split_rgb;
	int		rgb_hex[3];
	int		i;
	int		hex;

	split_rgb = ft_split(rgb, ',');
	if (!split_rgb)
		return (-1);
	if (ft_split_len(split_rgb) != 3)
		return (ft_free_split(split_rgb), -1);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(split_rgb[i]))
			return (ft_free_split(split_rgb), -1);
		rgb_hex[i] = ft_atoi(split_rgb[i]);
		i++;
	}
	hex = (rgb_hex[0] << 16) | (rgb_hex[1] << 8) | rgb_hex[2];
	return (ft_free_split(split_rgb), hex);
}

static int	set_color(t_cub *cub, char **split_line)
{
	int	rgb;

	if (ft_split_len(split_line) != 2)
		return (-1);
	rgb = rgb2hex(split_line[1]);
	if (rgb == -1)
		return (7);
	if (ft_strcmp(split_line[0], "C") == 0)
	{
		if (cub->config.ceiling_color != -1)
			return (8);
		return (cub->config.ceiling_color = rgb, cub->config.config_count++, 0);
	}
	if (cub->config.floor_color != -1)
		return (8);
	return (cub->config.floor_color = rgb, cub->config.config_count++, 0);
}

int	set_config(t_cub *cub, char **split_line)
{
	if (ft_strcmp(split_line[0], "C") == 0
		|| ft_strcmp(split_line[0], "F") == 0)
		return (set_color(cub, split_line));
	return (set_texture_path(cub, split_line));
}
