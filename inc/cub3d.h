/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:53:56 by slayer            #+#    #+#             */
/*   Updated: 2026/07/27 00:31:22 by slayer           ###   ########.fr       */
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
# define EVENT_KEY_RELEASE 3
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

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define SIDE_X 0
# define SIDE_Y 1

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	DIRECTION_COUNT
}	t_direction;

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

//one image and its pixel metadata
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

//MLX connection, window, and frame image
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	frame;
}	t_mlx;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	spawn_dir;
	t_point	spawn_pos;
}	t_map;

//temporary raycasting calculations
typedef struct s_ray
{
	double	camera_x;
	t_vec2	dir;
	t_point	map;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_point	step;
	double	perp_wall_dist;
	int		side;
	int		hit;
}	t_ray;

//collection of four texture images
typedef struct s_textures
{
	t_img	wall[DIRECTION_COUNT];
}	t_textures;

//temporary drawing calculations
typedef struct s_render
{
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		texture_x;
	int		shade;
	double	step;
	double	tex_pos;
}	t_render;

//player input used in loops as 0 or 1
typedef struct s_input
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_input;

//paths and colors parsed from the file
typedef struct s_config
{
	char	*texture_path[DIRECTION_COUNT];
	int		floor_color;
	int		ceiling_color;
	int		config_count;
}	t_config;

//persistent application state
typedef struct s_cub
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_textures	textures;
	t_input		input;
	t_config	config;
}	t_cub;

/*
** parcing and map loading
*/
int			check_file_name(char const *argv);
int			load_map(char const *argv, t_cub *cub);
int			set_config(t_cub *cub, char **split_line);
int			has_xpm_ext(char *path);
t_direction	get_direction(char *token);
int			print_config_error(int code);
int			print_map_error(int code);
int			map_parser(t_cub *cub, int fd);
int			is_wall_or_void(t_map *map, int x, int y);
int			is_valid_map(t_cub *cub);
void		free_map_lines(char **lines, int count);
int			flood_fill_check(t_cub *cub);
void		trim_trailing_blank_lines(char **lines, t_cub *cub);
char		*skip_new_lines(int fd);
void		player_init(t_cub *cub);

/*
** Cleanup and exit
*/

void		free_config(t_config *config);
void		free_textures(t_mlx *mlx, t_textures *textures);
void		free_mlx(t_mlx *mlx);
void		free_cub(t_cub *cub);
void		free_map(t_map *map);
int			close_game(t_cub *cub);

/*
** Hooks
*/

void		setup_hooks(t_cub *cub);
int			handle_keypress(int keycode, void *param);
int			handle_keyrelease(int keycode, void *param);
int			game_loop(void *param);

/*
** Initialization
*/
void		init_map_vars(t_cub *cub);
int			init_cub(t_cub *cub);
int			init_mlx(t_cub *cub);

/*
** Rendering
*/

void		draw_background(t_cub *cub);
void		render_frame(t_cub *cub);
void		render_wall_columns(t_cub *cub);
void		cast_ray_for_column(t_cub *cub, int x);
void		put_pixel(t_img *img, int x, int y, int color);

/*
** Raycasting
*/

void		init_ray(t_cub *cub, t_ray *ray, int x);
void		init_dda(t_cub *cub, t_ray *ray);
void		perform_dda(t_cub *cub, t_ray *ray);
void		calculate_wall_projection(t_ray *ray, t_render *render);

/*
** Player movement
*/

void		update_player(t_cub *cub);
void		move_forward(t_cub *cub);
void		move_backward(t_cub *cub);
void		move_left(t_cub *cub);
void		move_right(t_cub *cub);
void		rotate_player(t_cub *cub, double angle);
int			can_move_to(t_map *map, double x, double y);

/*
** Texture loading
*/

int			calculate_wall_x(t_cub *cub, t_ray *ray);
int			calculate_texture_x(t_ray *ray, t_img *texture, double wall_x);
int			get_texture_pixel(t_img *texture, int x, int y);
void		init_texture_draw(t_render *render, t_img *texture);
void		draw_textured_wall(t_cub *cub, t_ray *ray,
				t_render *render, int screen_x);
int			load_texture(void *mlx, t_img *tex, char *path);
int			load_all_textures(t_cub *cub);
t_img		*get_wall_texture(t_cub *cub, t_ray *ray);
int			init_textures(t_cub *cub);
int			shade_color(int color);

#endif