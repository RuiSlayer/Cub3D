/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 01:31:43 by slayer            #+#    #+#             */
/*   Updated: 2026/07/16 00:21:23 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_map(char const *argv, t_cub *cub)
{
	int	fd;

/* 	if (check_file_name(argv))
		return (1); */
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (1);
	if (print_check_textures(load_textures(cub, fd)))
		return (close(fd), 1);
	
	return (close(fd), 0);
}
