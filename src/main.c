/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 19:06:02 by slayer            #+#    #+#             */
/*   Updated: 2026/07/27 18:07:43 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char const **argv)
{
	t_cub	cub;
	int		error_code;

	(void)argv;
	if (argc != 2)
		return (ft_dprintf(2, "Error\nA map should be pass as argument\n"));
	init_cub(&cub);
	error_code = load_map(argv[1], &cub);
	if (error_code == 2)
		ft_dprintf(2, "Error\nMap file not found!\n");
	if (error_code)
		return (free_cub(&cub), 1);
	player_init(&cub);
	if (init_mlx(&cub))
		return (free_cub(&cub), 1);
	if (init_textures(&cub))
		return (ft_dprintf(2, "Error\nTexture load fail!\n"),
			free_cub(&cub), 1);
	setup_hooks(&cub);
	render_frame(&cub);
	mlx_loop(cub.mlx.mlx);
	free_cub(&cub);
	return (0);
}
