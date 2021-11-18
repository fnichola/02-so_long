# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2021/11/18 21:28:05 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MiniLibx will automatically compile.
# Run 'make' if on MacOS
# Run 'make LINUX=1' if on Linux.
#
# If on Debian/Linux, install other dependencies with:
# sudo apt install gcc make xorg libxext-dev libbsd-dev

NAME = so_long

HEADER = includes/so_long.h

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -framework OpenGL -framework AppKit

ifdef LINUX
MLX_DIR = mlx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLXFLAGS = -lXext -lX11 -lm
CFLAGS += -D LINUX 
endif

SRCS = srcs/main.c \
	srcs/read_map.c \
	srcs/render_screen.c \
	srcs/pixel_utilities.c \
	srcs/load_sprites.c \
	srcs/check_map.c \
	srcs/game_control.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<
	
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB) $(HEADER)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_LIB)
	$(RM) $(MLX_LIB)


re: fclean all

.PHONY: all clean fclean re bonus
