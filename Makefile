# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:25:34 by thopgood          #+#    #+#              #
#    Updated: 2024/07/12 23:31:16 by thopgood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# * run `make download` to download dependencies
# * run `make` to compile binary
# * run `make remove` to remove dependencies

NAME 		= so_long
BONUS		= so_long_bonus

CC 			= cc
RM 			= rm -rf
INCLUDE 	= -Iinclude

MLX_INCLUDE = -I/usr/include -Imlx -O3
MLX_FLAGS 	= -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
GET_MLX 	= curl -O https://cdn.intra.42.fr/document/document/21389/minilibx-linux.tgz
MLX_TAR 	= minilibx-linux

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -O0 # -fsanitize=address

SRC_DIR 	= src/
SRC_B_DIR	= src_bonus/
OBJ_DIR 	= obj/
LIBFT_DIR 	= libft/
MLX_DIR		= mlx/
LIBFT		= -L $(LIBFT_DIR) -lft

UNTAR		= tar -xvf

SRC 		= 	so_long.c \
				map_parse.c \
				map_validity.c \
				flood_fill.c \
				gfx_load.c \
				gfx_render.c \
				move.c \
				move2.c \
				error.c \
				free.c

SRC_B 		= 	so_long_bonus.c \
				game_bonus.c \
				map_parse_bonus.c \
				map_validity_bonus.c \
				flood_fill_bonus.c \
				gfx_load_bonus.c \
				gfx_render_bonus.c \
				gfx_render2_bonus.c \
				sprite_animation_bonus.c \
				sprite_animation2_bonus.c \
				move_bonus.c \
				move2_bonus.c \
				error_bonus.c \
				free_bonus.c

OBJ 		= 	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_B 		= 	$(addprefix $(OBJ_DIR), $(SRC_B:.c=.o))

all: $(NAME)

download:
	@echo ""${BLUE}$(MLX_TAR)""${NC}Downloading...""
	@$(GET_MLX)
	@echo ""${GREEN}Downloaded""$(NC)""
	@echo ""${BLUE}$(MLX_TAR)""${NC}Unpacking..."\c"
	@$(UNTAR) $(MLX_TAR).tgz > /dev/null
	@echo ""${GREEN}Unpacked""$(NC)""
	@mv $(MLX_TAR) $(MLX_DIR)
	@rm -f $(MLX_TAR).tgz

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_B_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) > /dev/null
	@echo ""${BLUE}$(NAME)""${NC}Compiling... "\c"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo ""${GREEN}Complete""$(NC)""

$(BONUS): $(OBJ_B)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) > /dev/null
	@echo ""${BLUE}$(NAME)""${NC}Compiling bonus... "\c"
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) $(MLX_FLAGS) -o $(NAME)_bonus
	@echo ""${GREEN}Complete""$(NC)""

bonus: $(BONUS)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@cd $(MLX_DIR) && $(MAKE) clean > /dev/null
	@echo ""${BLUE}$(NAME)""${NC}Cleaning..."\c"
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_B_DIR)
	@echo ""${GREEN}Complete""$(NC)""

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@$(RM) $(NAME) $(BONUS)

remove:
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re bonus

# Colours
WHITE	=	'\033[0;37m'
YELLOW	=	'\033[0;33m'
BLUE	=	'\033[0;34m'
GREEN	=	'\033[0;32m'
RED		=	'\033[0;31m'
NC		=	'\033[0m' # no colour
#> /dev/null