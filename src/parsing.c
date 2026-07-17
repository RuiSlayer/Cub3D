/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:40:39 by slayer            #+#    #+#             */
/*   Updated: 2026/07/17 05:11:35 by slayer           ###   ########.fr       */
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
	return (ft_strcmp(path + len - 4, ".xpm"));
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

	if (ft_split_len(split_line) != 3)
		return (ft_free_split(split_line), -1);
	if (!has_xpm_ext(split_line[1]))
		return (4);
	fd = open(split_line[1], O_RDONLY);
	if (fd < 0)
		return (5);
	dir = get_direction(split_line[0]);
	if (dir == DIRECTION_COUNT)
		return (-1);
	if(cub->config.texture_path[dir] != NULL)
		return (9);
	cub->config.texture_path[dir] = ft_strdup(split_line[1]);
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
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
		if (rgb_hex[i] < 0 || rgb_hex[i] > 255)
			return (ft_free_split(split_rgb), -1);
		i++;
	}
	return (ft_free_split(split_rgb), (rgb_hex[0] << 16) | (rgb_hex[1] << 8) | rgb_hex[2]);
}

static int	set_color(t_cub *cub, char **split_line)
{
	int	rgb;

	if ((rgb = rgb2hex(split_line[1])) == -1)
		return (7);
	if (ft_strcmp(split_line[0], "C") == 0)
	{
		if (cub->config.ceiling_color != -1)
			return (cub->config.ceiling_color = rgb, 0);
		else
			return (8);
	}
	if (cub->config.floor_color != -1)
		return (cub->config.floor_color = rgb, 0);
	return (8);
}

static int	set_config(t_cub *cub, char **split_line)
{

	if (ft_strcmp(split_line[0], "C") == 0 || ft_strcmp(split_line[0], "F") == 0)
		return (set_color(cub, split_line));
	return (set_texture_path(cub, split_line), 0);
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
	int					i;

	error_code = 0;
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (!line)
			return (2);
		split_line = ft_split(line, ' ');
		free(line);
		if ((error_code = is_config(split_line[0])))
			return (ft_free_split(split_line), error_code);
		if ((error_code = set_config(cub, split_line)))
			return (ft_free_split(split_line), error_code);
		ft_free_split(split_line);
		i++;
	}
	return (ft_free_split(split_line), 0);
}

// char	caracter_test(int i, int j, t_Level *level)
// {
// 	if (level->map[i][j] == '0' || level->map[i][j] == '1')
// 		return (level->map[i][j]);
// 	if (level->map[i][j] == 'E' && level->exit_init_pos->x == -1)
// 	{
// 		level->exit_init_pos->y = i;
// 		level->exit_init_pos->x = j;
// 		return (level->map[i][j]);
// 	}
// 	if (level->map[i][j] == 'E' && level->exit_init_pos->x != -1)
// 		return (ft_dprintf("Error\nThe map must have only one exit\n"), 'N');
// 	if (level->map[i][j] == 'P' && level->player_ini_pos->x == -1)
// 	{
// 		level->player_ini_pos->y = i;
// 		level->player_ini_pos->x = j;
// 		return (level->map[i][j]);
// 	}
// 	if (level->map[i][j] == 'P' && level->player_ini_pos->x != -1)
// 		return (ft_dprintf("Error\nthe map must have only one player\n"), 'N');
// 	if (level->map[i][j] == 'C')
// 	{
// 		level->colectables++;
// 		return (level->map[i][j]);
// 	}
// 	return (ft_dprintf("Error\nInvalid Caracter in map\n"), 'N');
// }

// int	check_map_syntax_aux(t_Level *level)
// {
// 	if (level->exit_init_pos->x == -1)
// 		return (ft_dprintf("Error\nThe map must contain an exit\n"), 1);
// 	if (level->player_ini_pos->x == -1)
// 		return (ft_dprintf("Error\nThe map must contain a player\n"), 1);
// 	if (level->colectables == 0)
// 		return (ft_dprintf("Error\nThe map must have one colectable\n"), 1);
// 	return (0);
// }

// int	check_map_syntax(t_Level *level)
// {
// 	int		i;
// 	int		j;
// 	int		last;

// 	i = 0;
// 	while (level->map[i])
// 	{
// 		j = 0;
// 		while (level->map[i][j] != '\n' && level->map[i][j])
// 		{
// 			if (caracter_test(i, j, level) == 'N')
// 				return (1);
// 			j++;
// 		}
// 		if (i > 0 && j != last)
// 			return (ft_dprintf("Error\nLines don't have same legth\n"), 1);
// 		last = j;
// 		i++;
// 	}
// 	if (check_map_syntax_aux(level))
// 		return (1);
// 	if (j == i)
// 		return (ft_dprintf("Error\nThe map must be a rectangle\n"), 1);
// 	level->limit->x = j - 1;
// 	return (0);
// }
