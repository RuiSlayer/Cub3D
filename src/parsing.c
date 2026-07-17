/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:40:39 by slayer            #+#    #+#             */
/*   Updated: 2026/07/17 06:34:54 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_file_name(char const *argv)
{
	int		i;
	int		j;
	char	*extencion;
	int		fd;

	if (argv[0] == '.')
		return (ft_dprintf(2, "Error\nThe file can't be a hidden file\n"), 1);
	i = ft_strlen(argv) - 1;
	j = 3;
	extencion = ".cub";
	while (j >= 0)
	{
		if (argv[i] != extencion[j])
			return (ft_dprintf
				(2, "Error\nYour file must be of the type .cub\n"), 1);
		i--;
		j--;
	}
	if (argv[i] == '/')
		return (ft_dprintf(2, "Error\nThe file can't be a hidden file\n"), 1);
	fd = open(argv, 0x10000);
	if (fd >= 0)
		return (close(fd),
			ft_dprintf(2, "Error\nThe file can't be a dir\n"), 1);
	return (0);
}

static int	has_xpm_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strcmp(path + len - 4, ".xpm") == 0);
}

static t_direction	get_direction(char *token)
{
	int	i;
	static const char	*config_type[] = {"NO", "SO", "WE", "EA"};

	i = 0;
	while (i < DIRECTION_COUNT)
	{
		if (ft_strcmp(token, config_type[i]) == 0)
			return (i);
		i++;
	}
	return (DIRECTION_COUNT);
}

static int	set_texture_path(t_cub *cub, char **split_line)
{
	t_direction	dir;
	int			fd;

	if (ft_split_len(split_line) != 2)
		return (-1);
	if (!has_xpm_ext(split_line[1]))
		return (4);
	fd = open(split_line[1], O_RDONLY);
	if (fd < 0)
		return (5);
	close(fd);
	dir = get_direction(split_line[0]);
	if (dir == DIRECTION_COUNT)
		return (-1);
	if(cub->config.texture_path[dir] != NULL)
		return (9);
	cub->config.texture_path[dir] = ft_strdup(split_line[1]);
	if (!cub->config.texture_path[dir])
		return (-1);
	cub->config.config_count++;
	return (0);
}

int	is_valid_number(char *str)
{
	int		i;
	long	value;

	if (!str || !str[0])
		return (0);
	i = 0;
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

	split_rgb = ft_split(rgb, ',');
	if (!split_rgb)
		return (-1);
	if (ft_split_len(split_rgb) != 3)
		return (ft_free_split(split_rgb), -1);
	i = 0;
	while (i < 3)
	{
		if (!split_rgb[i] || !is_valid_number(split_rgb[i]))
			return (ft_free_split(split_rgb), -1);
		rgb_hex[i] = ft_atoi(split_rgb[i]);
		i++;
	}
	return (ft_free_split(split_rgb), (rgb_hex[0] << 16) | (rgb_hex[1] << 8) | rgb_hex[2]);
}

static int	set_color(t_cub *cub, char **split_line)
{
	int	rgb;

	if (ft_split_len(split_line) != 2)
		return (-1);
	if ((rgb = rgb2hex(split_line[1])) == -1)
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

static int	set_config(t_cub *cub, char **split_line)
{

	if (ft_strcmp(split_line[0], "C") == 0 || ft_strcmp(split_line[0], "F") == 0)
		return (set_color(cub, split_line));
	return (set_texture_path(cub, split_line));
}

static int	is_config(char *type)
{
	static const char	*config_type[] = {"NO", "SO", "WE", "EA", "C", "F"};
	int					i;

	i = 0;
	while(i < 6)
	{
		if (ft_strcmp(type, config_type[i]) == 0)
			return (0);
		i++;
	}
	return (6);
}

int	load_config(t_cub *cub, int fd)
{
	char				**split_line;
	char				*line;
	int					error_code;

	error_code = 0;
	while (cub->config.config_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (2);
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line[0] || (ft_strcmp(split_line[0], "\n") == 0) && ((ft_split_len(split_line) == 1)))
		{
			ft_free_split(split_line);
			continue ;
		}
		if ((error_code = is_config(split_line[0])))
			return (ft_free_split(split_line), error_code);
		if ((error_code = set_config(cub, split_line)))
			return (ft_free_split(split_line), error_code);
		ft_free_split(split_line);
	}
	return (0);
}
