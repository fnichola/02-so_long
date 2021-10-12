# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2021/10/11 17:34:23 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

HEADER = so_long.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = srcs/hook_example.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = 

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef WITH_BONUS
OBJS += $(BONUS_OBJS)
endif


all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Imlx -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

bonus:
	$(MAKE) WITH_BONUS=1

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	$(RM) libft.so

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus