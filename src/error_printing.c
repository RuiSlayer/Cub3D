/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 13:22:24 by slayer            #+#    #+#             */
/*   Updated: 2026/07/14 15:12:35 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	print_check_textures(int code)
{
	if (code == 1)
		return (ft_dprintf(2, "Error\n can't open file!\n"), 1);
	if (code == 2)
		return (ft_dprintf(2, "Error\n NULL pointer exeception!\n"), 1);
	if (code == 3)
		return (ft_dprintf(2, "Error\n wrong direction passed!\n"), 1);
	if (code == 4)
		ft_dprintf(2, "Error\n texture file must be .xpm type file!\n", 1);
	if (code == 5)
		ft_dprintf(2, "Error\n can't open texture file!\n", 1);
	// if (code == 6)
	// 	ft_dprintf(2, "Error\n");
	// if (code == 7)
	// 	ft_dprintf(2, "Error\n");
	return (0);
}
