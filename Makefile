# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yukravch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 18:47:58 by yukravch          #+#    #+#              #
#    Updated: 2025/04/11 17:45:45 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = pipex

LIB = libft/libft.a

all: $(NAME)


SRC_DIR = sources
OBJ_DIR = objects
INC_DIR = includes -I libft/includes

FILES = main.c exit.c
SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CFLAGS = -Wall -Wextra -Werror -g3 -I $(INC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB)
	cc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	
$(LIB):
	make -C libft

clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(NAME)
re: fclean all
