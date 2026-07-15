NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O3 -std=gnu17

UNAME_S		:= $(shell uname -s)

LIBFT_DIR		= libs/42libft
PRINTF_DIR		= libs/ft_dprintf

LIBFT		= $(LIBFT_DIR)/libft.a
PRINTF		= $(PRINTF_DIR)/libftprintf.a

ifeq ($(UNAME_S),Darwin)

MLX_DIR		= libs/minilibx_opengl
MLX			= $(MLX_DIR)/libmlx.a

MLX_FLAGS	= -framework OpenGL -framework AppKit
MLX_CFLAGS	= -DGL_SILENCE_DEPRECATION

else ifeq ($(UNAME_S),Linux)

MLX_DIR		= libs/minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a

MLX_FLAGS	= -lXext -lX11 -lm -lz
MLX_CFLAGS	=

else

$(error Unsupported operating system)

endif

INCLUDES	= \
			-Iinc \
			-I$(MLX_DIR) \
			-I$(LIBFT_DIR) \
			-I$(PRINTF_DIR)

SRCS		= \
			src/main.c \
			src/init/init_mlx.c \
			src/rendering/render_smoke.c \
			src/hooks/hooks.c \
			src/cleanup/free_mlx.c \
			src/error_printing.c \
			src/init/load_map.c \
			src/parsing.c \
			libs/ft_get_next_line/get_next_line.c \
			libs/ft_get_next_line/get_next_line_utils.c

OBJ_DIR		= build
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) \
		$(LIBFT) \
		$(PRINTF) \
		$(MLX) \
		$(MLX_FLAGS) \
		-o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR) CFLAGS+="$(MLX_CFLAGS)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re