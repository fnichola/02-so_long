# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2021/10/22 17:56:14 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

HEADER = includes/so_long.h

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

SRCS = srcs/main.c \
	srcs/map.c \
	srcs/render.c \
	srcs/utilities.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = 

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef WITH_BONUS
OBJS += $(BONUS_OBJS)
endif

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
$(NAME): $(OBJS) $(LIBFT_LIB) $(HEADER)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_DIR)

bonus:
	$(MAKE) WITH_BONUS=1

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_LIB)


re: fclean all

.PHONY: all clean fclean re bonus
