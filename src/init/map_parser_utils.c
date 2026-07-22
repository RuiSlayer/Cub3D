/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:30:38 by slayer            #+#    #+#             */
/*   Updated: 2026/07/22 18:32:40 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*skip_new_lines(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (ft_strcmp(line, "\n") != 0)
			return (line);
	}
}

void	trim_trailing_blank_lines(char **lines, t_cub *cub)
{
	int	last;

	last = cub->map.height - 1;
	while (last >= 0 && lines[last][0] == '\0')
	{
		free(lines[last]);
		lines[last] = NULL;
		last--;
	}
	cub->map.height = last + 1;
}

void	free_map_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
