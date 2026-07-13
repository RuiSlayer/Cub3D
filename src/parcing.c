/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:40:39 by slayer            #+#    #+#             */
/*   Updated: 2026/07/13 17:14:29 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:34:30 by slayer            #+#    #+#             */
/*   Updated: 2025/11/13 00:44:35 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_file_name(char const *argv)
{
	int		i;
	int		j;
	char	*extencion;
	int		fd;

	if (argv[0] == '.')
		return (ft_dprintf(2, "Error\nThe file can't be a hidden file\n"), 1);
	i = ft_strlen(argv) - 1;
	j = 3;
	extencion = ".cub";
	while (j >= 0)
	{
		if (argv[i] != extencion[j])
			return (ft_dprintf
				(2, "Error\nYour file must be of the type .cub\n"), 1);
		i--;
		j--;
	}
	if (argv[i] == '/')
		return (ft_dprintf(2, "Error\nThe file can't be a hidden file\n"), 1);
	fd = open(argv, __O_DIRECTORY);
	if (fd >= 0)
		return (close(fd),
			ft_dprintf(2, "Error\nThe file can't be a dir\n"), 1);
	return (0);
}

//TODO function that tries to load texture
int	find_texture(char *texture)
{
	return (0);
}

int	check_textures(char const *argv)
{
	int					fd;
	int					i;
	char				*texture;
	static const char	*g_dir_names[] = {"NO", "SO", "WE", "EA"};

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	while (i < 4)
	{
		texture = get_next_line(fd);
		if (!texture)
			return (1);
		if (ft_strcmp(ft_substr(texture, 0, 1) , g_dir_names[i]))
			return (1);
		find_texture(texture);
		i++;
	}
	return (0);
}

// char	caracter_test(int i, int j, t_Level *level)
// {
// 	if (level->map[i][j] == '0' || level->map[i][j] == '1')
// 		return (level->map[i][j]);
// 	if (level->map[i][j] == 'E' && level->exit_init_pos->x == -1)
// 	{
// 		level->exit_init_pos->y = i;
// 		level->exit_init_pos->x = j;
// 		return (level->map[i][j]);
// 	}
// 	if (level->map[i][j] == 'E' && level->exit_init_pos->x != -1)
// 		return (ft_dprintf("Error\nThe map must have only one exit\n"), 'N');
// 	if (level->map[i][j] == 'P' && level->player_ini_pos->x == -1)
// 	{
// 		level->player_ini_pos->y = i;
// 		level->player_ini_pos->x = j;
// 		return (level->map[i][j]);
// 	}
// 	if (level->map[i][j] == 'P' && level->player_ini_pos->x != -1)
// 		return (ft_dprintf("Error\nthe map must have only one player\n"), 'N');
// 	if (level->map[i][j] == 'C')
// 	{
// 		level->colectables++;
// 		return (level->map[i][j]);
// 	}
// 	return (ft_dprintf("Error\nInvalid Caracter in map\n"), 'N');
// }

// int	check_map_syntax_aux(t_Level *level)
// {
// 	if (level->exit_init_pos->x == -1)
// 		return (ft_dprintf("Error\nThe map must contain an exit\n"), 1);
// 	if (level->player_ini_pos->x == -1)
// 		return (ft_dprintf("Error\nThe map must contain a player\n"), 1);
// 	if (level->colectables == 0)
// 		return (ft_dprintf("Error\nThe map must have one colectable\n"), 1);
// 	return (0);
// }

// int	check_map_syntax(t_Level *level)
// {
// 	int		i;
// 	int		j;
// 	int		last;

// 	i = 0;
// 	while (level->map[i])
// 	{
// 		j = 0;
// 		while (level->map[i][j] != '\n' && level->map[i][j])
// 		{
// 			if (caracter_test(i, j, level) == 'N')
// 				return (1);
// 			j++;
// 		}
// 		if (i > 0 && j != last)
// 			return (ft_dprintf("Error\nLines don't have same legth\n"), 1);
// 		last = j;
// 		i++;
// 	}
// 	if (check_map_syntax_aux(level))
// 		return (1);
// 	if (j == i)
// 		return (ft_dprintf("Error\nThe map must be a rectangle\n"), 1);
// 	level->limit->x = j - 1;
// 	return (0);
// }
