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
			src/init/init_debug_scene.c \
			src/rendering/render_frame.c \
			src/rendering/background.c \
			src/rendering/draw_column.c \
			src/rendering/raycast.c \
			src/rendering/dda.c \
			src/hooks/hooks.c \
			src/movement/player_move.c \
			src/movement/player_rotate.c \
			src/movement/player_update.c \
			src/movement/collision.c \
			src/cleanup/free_mlx.c \
			src/cleanup/free_map.c \
			src/error_printing.c \
			src/init/load_map.c \
			src/init/config_loader.c \
			src/init/config_loader_utils.c \
			src/init/map_parser.c \
			src/init/map_parser_utils.c \
			src/init/validate_map.c \
			src/init/player_init.c \
			libs/ft_get_next_line/get_next_line.c \
			libs/ft_get_next_line/get_next_line_utils.c

OBJ_DIR		= build
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
VALGRIND = valgrind --trace-children=yes --show-leak-kinds=all --leak-check=full --track-origins=yes -s --track-fds=all

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

ARGS ?= maps/test.cub


mlx:
	@cd $(MLX_DIR) && git clone https://github.com/42Paris/minilibx-linux.git

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $(ARGS) 2>&1 | tee valgrind.log

mlxclean:
	@rm -rf $(MLX_DIR)
	@echo "MLX deleted"

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