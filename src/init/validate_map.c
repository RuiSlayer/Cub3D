/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:24:33 by slayer            #+#    #+#             */
/*   Updated: 2026/07/22 18:28:52 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	**dup_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
			return (free_map_lines(copy, i), NULL);
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

static int	is_valid_tile(t_cub *cub, char **grid, int x, int y)
{
	if (y < 0 || y >= cub->map.height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(grid[y]))
		return (0);
	if (grid[y][x] == ' ')
		return (0);
	return (1);
}

int	flood_fill_check(t_cub *cub)
{
	char	**grid;
	t_point	*stack;
	t_point	p;
	int		top;

	grid = dup_grid(cub->map.grid, cub->map.height);
	if (!grid)
		return (1);
	stack = malloc(sizeof(t_point) * (cub->map.width * cub->map.height * 4));
	if (!stack)
		return (free_map_lines(grid, cub->map.height), 2);
	top = 0;
	stack[top].x = cub->map.spawn_pos.x;
	stack[top].y = cub->map.spawn_pos.y;
	top++;
	while (top > 0)
	{
		top--;
		p = stack[top];
		if (!is_valid_tile(cub, grid, p.x, p.y))
			return (free(stack), free_map_lines(grid, cub->map.height), 3);
		if (grid[p.y][p.x] == '1' || grid[p.y][p.x] == 'V')
			continue ;
		grid[p.y][p.x] = 'V';
		stack[top++] = (t_point){p.x + 1, p.y};
		stack[top++] = (t_point){p.x - 1, p.y};
		stack[top++] = (t_point){p.x, p.y + 1};
		stack[top++] = (t_point){p.x, p.y - 1};
	}
	return (free(stack), free_map_lines(grid, cub->map.height), 0);
}
