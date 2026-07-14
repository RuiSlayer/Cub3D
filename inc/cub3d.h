/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:53:56 by slayer            #+#    #+#             */
/*   Updated: 2026/07/14 01:36:27 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/ft_get_next_line/get_next_line.h"
# include "../libs/42libft/libft.h"
# include "../libs/ft_dprintf/ft_printf.h"
# include "math.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# if defined(__APPLE__)
#  include "../libs/minilibx_opengl/mlx.h"
# else
#  include "../libs/minilibx-linux/mlx.h"
# endif

/*
** Window configuration
*/

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

/*
** Return values
*/

# define SUCCESS 0
# define FAILURE 1

/*
** MLX events
*/

# define EVENT_KEY_PRESS 2
# define EVENT_DESTROY 17

/*
** Event masks
*/

# define MASK_NO_EVENT    0L
# define MASK_KEY_PRESS   1L   /* 1L << 0 */
# define MASK_KEY_RELEASE 2L   /* 1L << 1 */
# define MASK_EXPOSURE    4L   /* 1L << 2 */
# define MASK_STRUCTURE   32L  /* 1L << 5 */
/*
** Platform-specific keycodes
*/

# if defined(__APPLE__)
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

enum e_directions
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_player
{
	t_vec2	pos;    // position on the map, e.g. (23.5, 12.5)
	t_vec2	dir;    // direction vector, e.g. (-1, 0)
	t_vec2	plane;  // camera plane, perpendicular to dir
}	t_player;

typedef struct s_ray
{
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	side_dist;
	t_point	map_pos;   // integer cell the ray is currently in
	int		side;      // 0 = X-side hit, 1 = Y-side hit
}	t_ray;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	dir[4];
}	t_textures;

typedef struct s_cell
{
	char			symbol;
	int				texture_id;
}	t_cell;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	frame;
}	t_mlx;

typedef struct s_cub
{
	t_mlx	mlx;
	t_textures textures;
}	t_cub;

/*
** parcing and map loading
*/
int	load_map(char const *argv, t_cub cub);
int	check_file_name(char const *argv);
int	check_textures(char const *argv, t_cub cub);

/*
** Cleanup and exit
*/

void	free_cub(t_cub *cub);
int		close_game(t_cub *cub);

/*
** Hooks
*/

void	setup_hooks(t_cub *cub);
int		handle_keypress(int keycode, void *param);

/*
** Initialization
*/

void	init_cub(t_cub *cub);
int		init_mlx(t_cub *cub);

/*
** Rendering
*/

void	put_pixel(t_img *img, int x, int y, int color);
void	render_smoke_frame(t_cub *cub);

#endif