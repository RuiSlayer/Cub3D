/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 01:31:43 by slayer            #+#    #+#             */
/*   Updated: 2026/07/22 22:43:13 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_config(char *type)
{
	static const char	*config_type[] = {"NO", "SO", "WE", "EA", "C", "F"};
	int					i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(type, config_type[i]) == 0)
			return (0);
		i++;
	}
	return (6);
}

static int	load_config_loop(t_cub *cub, int fd)
{
	char				**split_line;
	char				*line;
	int					error_code;

	error_code = 0;
	line = get_next_line(fd);
	if (!line)
		return (2);
	if (ft_strcmp(line, "\n") == 0)
		return (free(line), 0);
	split_line = ft_split(line, ' ');
	free(line);
	if (!split_line)
		return (2);
	error_code = is_config(split_line[0]);
	if (error_code)
		return (ft_free_split(split_line), error_code);
	error_code = set_config(cub, split_line);
	if (error_code)
		return (ft_free_split(split_line), error_code);
	return (ft_free_split(split_line), 0);
}

static int	load_config(t_cub *cub, int fd)
{
	int	error_code;

	while (cub->config.config_count < 6)
	{
		error_code = load_config_loop(cub, fd);
		if (error_code)
			return (error_code);
	}
	return (0);
}

int	load_map(char const *argv, t_cub *cub)
{
	int	fd;

	if (check_file_name(argv))
		return (1);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (1);
	if (print_config_error(load_config(cub, fd)))
		return (close(fd), 1);
	ft_dprintf(2, "textures and colors saved with sucess!\n");
	if (print_map_error(map_parser(cub, fd)))
		return (close(fd), 1);
	close(fd);
	flood_fill_check(cub);
	ft_dprintf(2, "map loaded with sucess!\n");
	return (0);
}
