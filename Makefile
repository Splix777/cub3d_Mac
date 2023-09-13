# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 16:04:04 by fsalazar          #+#    #+#              #
#    Updated: 2023/09/13 18:36:33 by fsalazar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS = -lft -lftprintf

RM = rm -f

SRC_DIR = .
OBJ_DIR = obj

SRCS =	main.c \
		init/init_game.c \
		init/init_mlx.c \
		init/init_player.c \
		init/init_textures.c \
		misc/debug_utils.c \
		misc/frees.c \
		misc/utils.c \
		misc/utils2.c \
		parse/check_utils.c \
		parse/f_map_finalize.c \
		parse/load_full_map.c \
		parse/map_wall_checks.c \
		parse/parse_f_map.c \
		parse/parse_f_map2.c \
		parse/parse_rgb.c \
		parse/parse_textures.c \
		raycast/draw_frame.c \
		raycast/init_text_pixels.c \
		raycast/raycast_utils.c \
		raycast/raycast_utils2.c \
		raycast/raycast.c \
		raycast/render_frame.c \
		movement/key_input.c \
		movement/move_player.c \
		movement/check_valid_move.c \
		movement/rotate_player.c \

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m
CHECKMARK = ✔

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -L$(PRINTF_DIR) $(LDFLAGS) $(MLXFLAGS)
	@echo "$(GREEN)$(CHECKMARK) $(NAME) created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(YELLOW)$(CHECKMARK) $(NAME) cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	@make -C $(MLX_DIR) fclean
	@echo "$(RED)$(CHECKMARK) $(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
