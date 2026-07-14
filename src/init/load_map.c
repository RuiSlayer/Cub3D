/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 01:31:43 by slayer            #+#    #+#             */
/*   Updated: 2026/07/14 14:08:10 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_map(char const *argv, t_cub	*cub)
{
	if (check_file_name(argv))
		return (1);
	print_check_textures(load_textures(argv, cub));
		return (1);
	return (0);
}
