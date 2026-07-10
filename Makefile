###############################################################################
# Program
###############################################################################

NAME		= cub3D

###############################################################################
# Compiler
###############################################################################

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

###############################################################################
# OS Detection
###############################################################################

UNAME_S		:= $(shell uname -s)

###############################################################################
# Libraries
###############################################################################

LIBFT_DIR	= libs/42libft
PRINTF_DIR	= libs/ft_dprintf

LIBFT		= $(LIBFT_DIR)/libft.a
PRINTF		= $(PRINTF_DIR)/libftprintf.a

###############################################################################
# MiniLibX
###############################################################################

ifeq ($(UNAME_S),Darwin)

	MLX_DIR			= libs/minilibx_opengl
	MLX				= $(MLX_DIR)/libmlx.a

	MLX_FLAGS		= \
					-framework OpenGL \
					-framework AppKit

	MLX_CFLAGS		= -DGL_SILENCE_DEPRECATION

else ifeq ($(UNAME_S),Linux)

	MLX_DIR			= libs/minilibx-linux
	MLX				= $(MLX_DIR)/libmlx.a

	MLX_FLAGS		= \
					-lXext \
					-lX11 \
					-lm \
					-lz

	MLX_CFLAGS		=

else

$(error Unsupported operating system)

endif

###############################################################################
# Includes
###############################################################################

INCLUDES	= \
				-Iinc \
				-I$(MLX_DIR) \
				-I$(LIBFT_DIR) \
				-I$(PRINTF_DIR)

###############################################################################
# Sources
###############################################################################

SRCS		= \
				src/main.c \
				src/init/init_mlx.c \
				src/rendering/render_smoke.c \
				src/hooks/hooks.c \
				src/cleanup/free_mlx.c

###############################################################################
# Objects
###############################################################################

OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)

###############################################################################
# Rules
###############################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(MLX_DIR) CFLAGS+="$(MLX_CFLAGS)"
	$(CC) $(CFLAGS) $(OBJS) \
		$(LIBFT) \
		$(PRINTF) \
		$(MLX) \
		$(MLX_FLAGS) \
		-o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re