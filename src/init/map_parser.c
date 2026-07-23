/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 19:17:15 by slayer            #+#    #+#             */
/*   Updated: 2026/07/23 20:01:32 by slayer           ###   ########.fr       */
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
	int	error_code;

	error_code = 0;
	i = 0;
	while (line[i])
	{
		error_code = is_valid_char(line[i], cub);
		if (error_code == 0)
			return (3);
		else if (error_code == 2)
		{
			cub->map.spawn_pos.x = i;
			cub->map.spawn_pos.y = y;
		}
		else if (error_code == 3)
			return (4);
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

char	**collect_map_lines(int fd, char *line, t_cub *cub, int *error_code)
{
	char	**lines;
	int		capacity;
	int		count;

	capacity = 16;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (*error_code = 2, NULL);
	count = 0;
	while (line)
	{
		lines = grow_lines_if_needed(lines, count, &capacity);
		if (!lines)
			return (*error_code = 2, NULL);
		ft_trim_newline(line);
		*error_code = check_for_invalid_chars(line, count, cub);
		if (*error_code)
			return (free(line), free_map_lines(lines, count), NULL);
		lines[count++] = line;
		line = get_next_line(fd);
	}
	*error_code = 0;
	cub->map.height = count;
	return (lines);
}

int	map_parser(t_cub *cub, int fd)
{
	char	*line;
	char	**lines;
	int		i;
	int		error_code;

	line = skip_new_lines(fd);
	if (!line)
		return (1);
	init_map_vars(cub);
	lines = collect_map_lines(fd, line, cub, &error_code);
	if (!lines)
		return (error_code);
	lines[cub->map.height] = NULL;
	if (cub->map.spawn_dir == 'X')
		return (ft_free_split(lines), 4);
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

void	print_map(t_cub *cub)
{
	int i;
	for (i = 0; i < cub->map.height; i++)
	{
		printf("line %i: %s\n",i+1, cub->map.grid[i]);
	}
}
