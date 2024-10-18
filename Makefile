# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2024/10/18 14:21:21 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
B_NAME = bonus

HEADER_DIR = include
B_HEADER_DIR = include_bonus

SRC_DIR = src
B_SRC_DIR = src_bonus

OBJ_DIR = obj
B_OBJ_DIR = obj_bonus

CC = gcc
CFLAGS = -g -Werror -Wextra -Wall -Wunused-result -pedantic -I$(HEADER_DIR) -Imlx_linux
MLXFLAGS = -lmlx_Linux -lXext -lX11 -lm -lz -lft
LIB = libft.a
MLX = libmlx_Linux.a
LIB_DIR = lib
MLX_DIR = mlx_linux
LIB_PATH = $(LIB_DIR)/$(LIB)
MLX_PATH = $(MLX_DIR)/$(MLX)

SRCS = $(shell find $(SRC_DIR) -name '*.c')
B_SRCS = $(shell find $(B_SRC_DIR) -name '*.c')

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
B_OBJS = $(B_SRCS:$(B_SRC_DIR)/%.c=$(B_OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIB_DIR) -L$(MLX_DIR) $(MLXFLAGS)

$(B_NAME): $(B_OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	$(CC) $(CFLAGS) $^ -o $(B_NAME) -L$(LIB_DIR) -L$(MLX_DIR) $(MLXFLAGS)

fanalyzer: $(OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	$(CC) $(CFLAGS) -fanalyzer $^ -o $@ -L$(LIB_DIR) -L$(MLX_DIR) $(MLXFLAGS)

sanitize-thread: $(OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	$(CC) $(CFLAGS) -fsanitize=thread $^ -o $@ -L$(LIB_DIR) -L$(MLX_DIR) $(MLXFLAGS)

sanitize-addr: $(OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	$(CC) $(CFLAGS) -fsanitize=address $^ -o $@ -L$(LIB_DIR) -L$(MLX_DIR) $(MLXFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/include -I$(HEADER_DIR) -Imlx_linux -c $< -o $@

$(B_OBJ_DIR)/%.o:	$(B_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/include -I$(HEADER_DIR) -Imlx_linux -c $< -o $@

$(LIB_PATH):
	@echo "Running libft make"
	@(cd $(LIB_DIR) && make)

$(MLX_PATH):
	@echo "Running mlx make"
	@(cd $(MLX_DIR) && make)

clean:
	@echo "Removing all object files"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(B_OBJ_DIR)
	@(cd $(LIB_DIR) && make clean)
	@(cd $(MLX_DIR) && make clean)

fclean: clean
	@echo "Removing all object files and executable"
	@rm -rf $(NAME) sanitize-thread sanitize-addr
	@rm -rf $(B_NAME) sanitize-thread sanitize-addr

re:	fclean all

.PHONY: all clean fclean re
