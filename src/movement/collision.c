/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:26:19 by fgameiro          #+#    #+#             */
/*   Updated: 2026/07/27 00:00:06 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	can_move_to(t_map *map, double x, double y)
{
	if (is_wall_or_void(map, (int)(x - 0.20), (int)(y - 0.20)))
		return (0);
	if (is_wall_or_void(map, (int)(x + 0.20), (int)(y - 0.20)))
		return (0);
	if (is_wall_or_void(map, (int)(x - 0.20), (int)(y + 0.20)))
		return (0);
	if (is_wall_or_void(map, (int)(x + 0.20), (int)(y + 0.20)))
		return (0);
	return (1);
}
