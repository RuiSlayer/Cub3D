/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:22:24 by slayer            #+#    #+#             */
/*   Updated: 2026/07/23 20:18:22 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	print_config_error(int code)
{
	if (code == 0)
		return (0);
	if (code == 1)
		return (ft_dprintf(2, "Error\nCan't open file!\n"), 1);
	if (code == 2)
		return (ft_dprintf(2, "Error\nNULL pointer exeception!\n"), 1);
	if (code == 3)
		return (ft_dprintf(2, "Error\nInvalid config in file!\n"), 1);
	if (code == 4)
		return (ft_dprintf(2, "Error\nTexture file must be .xpm type file!\n", 1));
	if (code == 5)
		return (ft_dprintf(2, "Error\nCan't open texture file!\n", 1));
	if (code == 6)
		return (ft_dprintf(2, "Error\nInvalid Dir or Celing/Floor Caracter!"));
	if (code == 7)
		return (ft_dprintf(2, "Error\nInvalid RGB values!"));
	if (code == 8)
		return (ft_dprintf(2, "Error\nDuplicate seting for ceiling/floor color!"));
	if (code == 9)
		return (ft_dprintf(2, "Error\nDuplicate direction!"));
	return (0);
}

int	print_map_error(int code)
{
	if (code == 1)
		return (ft_dprintf(2, "Error\nNULL pointer exeception in line!\n"), 1);
	if (code == 2)
		return (ft_dprintf(2, "Error\nNULL pointer exeception in lines!\n"), 1);
	if (code == 3)
		return (ft_dprintf(2, "Error\nInvalid CHAR found in map!\n"), 1);
	if (code == 4)
		return (ft_dprintf(2, "Error\nDuplicate Player found in map!\n"), 1);
	if (code == 5)
		return (ft_dprintf(2, "Error\nNULL pointer exeception in grid!\n"), 1);
	if (code == 6)
		return (ft_dprintf(2, "Error\nNULL pointer exeception in stack!\n"), 1);
	if (code == 7)
		return (ft_dprintf(2, "Error\nMap should be surranded by walls!\n"), 1);
	return (0);
}
