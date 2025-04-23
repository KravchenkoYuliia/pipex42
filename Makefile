# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yukravch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 18:47:58 by yukravch          #+#    #+#              #
#    Updated: 2025/04/19 15:42:21 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIB = libft/libft.a

all: $(NAME)

SRC_DIR = sources
OBJ_DIR = objects
INC_DIR = includes -I libft/includes

FILES = pipex.c first_process.c second_process.c exit.c
SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CFLAGS = -Wall -Wextra -Werror -g3 -I $(INC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB)
	cc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

# ********************************************************************************* #
NAME_BONUS = pipex_bonus
bonus: $(NAME_BONUS)
FILES_BONUS = pipex_bonus.c check_files_bonus.c child_bonus.c handle_heredoc_bonus.c exit.c
SRC_BONUS = $(addprefix $(SRC_DIR)/, $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(FILES_BONUS:.c=.o))
$(NAME_BONUS): $(OBJ_BONUS) $(LIB)
	cc $(CFLAGS) $(OBJ_BONUS) $(LIB) -o $(NAME_BONUS)
# ********************************************************************************* #

$(LIB):
	make -C libft

clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
re: fclean all bonus
