# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 17:29:24 by mlitvino          #+#    #+#              #
#    Updated: 2025/02/26 18:47:29 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)/$(INCLD_DIR) -I$(INCLD_DIR)

NAME = fdf
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a

SRC_DIR = ./sources
OBJ_DIR = ./objects
LIBFT_DIR = ./libft
INCLD_DIR = ./includes
MLX_DIR = ./minilibx-linux-master

SRC = checks.c draw.c fdf.c get_map.c hooks.c inits.c utils.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
INCLD = $(INCLD_DIR)/fdf.h

.SECONDARY: $(OBJ)

all: $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I/usr/include -I$(MLX_DIR) -O3 -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX) | $(OBJ_DIR)
	$(CC) $(OBJ) $(LIBFT) -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $@
	make delete_obj_dir

$(LIBFT):
	make -C $(LIBFT_DIR) all
	make -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

delete_obj_dir:
	if [ -z "$$(ls -A $(OBJ_DIR))" ]; then \
		rm -rf $(OBJ_DIR); \
	fi

re: fclean all

.PHONY: all clean fclean re delete_obj_dir
