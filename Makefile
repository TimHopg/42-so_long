# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:25:34 by thopgood          #+#    #+#              #
#    Updated: 2024/06/17 19:34:19 by thopgood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
RM = rm -rf
INCLUDE = -Iinclude # -I/opt/X11/include -Imlx # OSX
# INCLUDE = -I/opt/X11/include -Imlx -Iinclude # LINUX

# CFLAGS = -Wall -Wextra -Werror $(INCLUDE) # MAIN
# CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -O0 # valgrind
CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g # leaks
# CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -fsanitize=address # fsanitize

SRC_DIR 	= src/
OBJ_DIR 	= obj/
LIBFT_DIR 	= libft/
LIBFT		= -L $(LIBFT_DIR) -lft

SRC 		= 	so_long.c

OBJ 		= 	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@echo ""${BLUE}$(NAME)""${NC}Compiling... "\c"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	@echo ""${GREEN}Complete""$(NC)""

all: $(NAME)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@echo ""${BLUE}$(NAME)""${NC}Cleaning..."\c"
	@$(RM) $(OBJ_DIR)
	@echo ""${GREEN}Complete""$(NC)""

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
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