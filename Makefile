# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:25:34 by thopgood          #+#    #+#              #
#    Updated: 2024/07/11 10:35:19 by thopgood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# run `make download` to download dependencies
# run `make` to compile binary
# run `make remove` to remove dependencies

NAME = so_long

CC 			= cc
RM 			= rm -rf
INCLUDE 	= -Iinclude

MLX_INCLUDE = -I/usr/include -Imlx -O3
MLX_FLAGS 	= -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
GET_MLX 	= curl -O https://cdn.intra.42.fr/document/document/21389/minilibx-linux.tgz
MLX_TAR 	= minilibx-linux

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -O0 # -fsanitize=address

SRC_DIR 	= src/
OBJ_DIR 	= obj/
LIBFT_DIR 	= libft/
MLX_DIR		= mlx/
LIBFT		= -L $(LIBFT_DIR) -lft

UNTAR		= tar -xvf

SRC 		= 	so_long.c \
				map_parse.c \
				map_validity.c \
				flood_fill.c \
				load_gfx.c \
				render_gfx.c \
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
	-@cd $(LIBFT_DIR) && $(MAKE) clean
	-@cd $(MLX_DIR) && $(MAKE) clean > /dev/null
	-@echo ""${BLUE}$(NAME)""${NC}Cleaning..."\c"
	-@$(RM) $(OBJ_DIR)
	-@echo ""${GREEN}Complete""$(NC)""

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@$(RM) $(NAME)

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