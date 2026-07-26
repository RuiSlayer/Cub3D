/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_loader_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 18:32:56 by slayer            #+#    #+#             */
/*   Updated: 2026/07/27 00:04:49 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_file_name(char const *argv)
{
	int		i;
	int		j;
	char	*extencion;

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
	return (0);
}

int	has_xpm_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strcmp(path + len - 4, ".xpm"));
}

t_direction	get_direction(char *token)
{
	int					i;
	static const char	*config_type[] = {"NO", "SO", "WE", "EA"};

	i = 0;
	while (i < DIRECTION_COUNT)
	{
		if (ft_strcmp(token, config_type[i]) == 0)
			return (i);
		i++;
	}
	return (DIRECTION_COUNT);
}
