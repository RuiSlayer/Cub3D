#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# if defined(__APPLE__)
# include "../libs/minilibx_opengl/mlx.h"
# else
# include "../libs/minilibx-linux/mlx.h"
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

# define MASK_KEY_PRESS (1L << 0)
# define MASK_NO_EVENT 0L

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
}	t_cub;

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