/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:22:24 by slayer            #+#    #+#             */
/*   Updated: 2026/07/17 05:12:15 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	print_check_textures(int code)
{
	if (code == 0)
		return (0);
	if (code == 1)
		return (ft_dprintf(2, "Error\n can't open file!\n"), 1);
	if (code == 2)
		return (ft_dprintf(2, "Error\n NULL pointer exeception!\n"), 1);
	if (code == 3)
		return (ft_dprintf(2, "Error\n invalid config in file!\n"), 1);
	if (code == 4)
		ft_dprintf(2, "Error\n texture file must be .xpm type file!\n", 1);
	if (code == 5)
		ft_dprintf(2, "Error\n can't open texture file!\n", 1);
	if (code == 6)
		ft_dprintf(2, "Error\n invalid Dir or Celing/Floor Caracter!");
	if (code == 7)
		ft_dprintf(2, "Error\n invalid RGB values!");
	if (code == 8)
		ft_dprintf(2, "Error\n duplicate seting for ceiling/floor color!");
	if (code == 9)
		ft_dprintf(2, "Error\n duplicate direction texture!");
	return (0);
}
