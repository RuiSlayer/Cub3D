/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 19:17:15 by slayer            #+#    #+#             */
/*   Updated: 2026/07/22 22:40:51 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_valid_char(char c, t_cub *cub)
{
	if (c == ' ' || c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (cub->map.spawn_dir != 'X')
			return (3);
		cub->map.spawn_dir = c;
		return (2);
	}
	return (0);
}

int	check_for_invalid_chars(char *line, int y, t_cub *cub)
{
	int	i;
	int	val_return;

	val_return = 0;
	i = 0;
	while (line[i])
	{
		val_return = is_valid_char(line[i], cub);
		if (val_return == 0)
			return (1);
		else if (val_return == 2)
		{
			cub->map.spawn_pos.x = i;
			cub->map.spawn_pos.y = y;
		}
		else if (val_return == 3)
			return (3);
		i++;
	}
	return (0);
}

static char	**grow_lines_if_needed(char **lines, int count, int *capacity)
{
	if (count + 1 < *capacity)
		return (lines);
	lines = ft_realloc_array(lines, *capacity, *capacity * 2);
	if (lines)
		*capacity *= 2;
	return (lines);
}

char	**collect_map_lines(int fd, char *line, t_cub *cub)
{
	char	**lines;
	int		capacity;
	int		count;

	capacity = 16;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	count = 0;
	while (line)
	{
		lines = grow_lines_if_needed(lines, count, &capacity);
		if (!lines)
			return (NULL);
		ft_trim_newline(line);
		if (check_for_invalid_chars(line, count, cub))
			return (free(line), free_map_lines(lines, count), NULL);
		lines[count++] = line;
		line = get_next_line(fd);
	}
	cub->map.height = count;
	return (lines);
}

int	map_parser(t_cub *cub, int fd)
{
	char	*line;
	char	**lines;
	int		i;

	line = skip_new_lines(fd);
	if (!line)
		return (1);
	init_map_vars(cub);
	lines = collect_map_lines(fd, line, cub);
	if (!lines)
		return (2);
	lines[cub->map.height] = NULL;
	if (cub->map.spawn_dir == 'X')
		return (ft_free_split(lines), 3);
	trim_trailing_blank_lines(lines, cub);
	i = 0;
	while (lines[i])
	{
		if ((int)ft_strlen(lines[i]) > cub->map.width)
			cub->map.width = ft_strlen(lines[i]);
		i++;
	}
	cub->map.grid = lines;
	return (0);
}
