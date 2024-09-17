# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:25:34 by thopgood          #+#    #+#              #
#    Updated: 2024/09/17 15:57:11 by thopgood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# * run `make download` to download dependencies
# * run `make` to compile binary

NAME 		= so_long

CC 			= cc
RM 			= rm -rf
INCLUDE 	= -Iinclude

MLX_INCLUDE = -I/usr/include -Imlx -O3
MLX_FLAGS 	= -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
GET_MLX 	= curl -O https://cdn.intra.42.fr/document/document/27192/minilibx-linux.tgz
MLX_TAR 	= minilibx-linux

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) # -g -O0 -fsanitize=address

SRC_DIR 	= src/
OBJ_DIR 	= obj/
LIBFT_DIR 	= libft/
MLX_DIR		= mlx/
LIBFT		= -L $(LIBFT_DIR) -lft

UNTAR		= tar -xzf

SRC 		= 	so_long.c \
				game.c \
				map_parse.c \
				map_validity.c \
				flood_fill.c \
				gfx_load.c \
				gfx_load2.c \
				gfx_render.c \
				gfx_render2.c \
				sprite_animation.c \
				sprite_animation2.c \
				move.c \
				move2.c \
				error.c \
				free.c

OBJ 		= 	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

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

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) > /dev/null
	@echo ""${BLUE}$(NAME)""${NC}Compiling... "\c"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo ""${GREEN}Complete""$(NC)""

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@echo ""${BLUE}$(NAME)""${NC}Cleaning..."\c"
	@$(RM) $(OBJ_DIR)
	@$(RM) $(MLX_TAR).tgz
	@rm -rf $(MLX_TAR)
	@echo ""${GREEN}Complete""$(NC)""

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@$(RM) $(NAME)
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re

# Colours
WHITE	=	'\033[0;37m'
YELLOW	=	'\033[0;33m'
BLUE	=	'\033[0;34m'
GREEN	=	'\033[0;32m'
RED		=	'\033[0;31m'
NC		=	'\033[0m' # no colour
#> /dev/null

norm:
	norminette ./src ./include

valman%:
	valgrind --leak-check=full --track-fds=all --track-origins=yes --show-reachable=yes -s ./so_long maps/$*.ber

man%:
	./so_long maps/$*.ber

valbon%:
	valgrind --leak-check=full --track-fds=all --track-origins=yes --show-reachable=yes -s ./so_long maps/bonus/$*.ber

bon%:
	./so_long maps/bonus/$*.ber