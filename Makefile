# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:25:34 by thopgood          #+#    #+#              #
#    Updated: 2024/06/18 16:30:52 by thopgood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC 			= cc
RM 			= rm -rf
INCLUDE 	= -Iinclude

ifeq ($(shell uname), Linux)
	MLX_INCLUDE = -I/usr/include -Imlx -O3
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
# -L/usr/lib/X11
else # OSX
	MLX_INCLUDE = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

# CFLAGS = -Wall -Wextra -Werror $(INCLUDE) # MAIN
# CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -O0 # valgrind
CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g # leaks
# CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -fsanitize=address # fsanitize

SRC_DIR 	= src/
OBJ_DIR 	= obj/
LIBFT_DIR 	= libft/
MLX_DIR		= mlx/
LIBFT		= -L $(LIBFT_DIR) -lft

SRC 		= 	so_long.c

OBJ 		= 	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(MLX_LIB) $(NAME)
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@ 

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@echo ""${BLUE}$(NAME)""${NC}Compiling... "\c"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo ""${GREEN}Complete""$(NC)""

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@cd $(MLX_DIR) && $(MAKE) clean
	@echo ""${BLUE}$(NAME)""${NC}Cleaning..."\c"
	@$(RM) $(OBJ_DIR)
	@echo ""${GREEN}Complete""$(NC)""

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@cd $(MLX_DIR) && $(MAKE) fclean
	@$(RM) $(NAME)
	@$(RM) $(BONUS)

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