/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 01:31:43 by slayer            #+#    #+#             */
/*   Updated: 2026/07/14 02:00:17 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_map(char const *argv, t_cub	cub)
{
	if (check_file_name(argv))
		return (1);
	if (check_textures(argv, cub))
		return (2);
	return (0);
}
