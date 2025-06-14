# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntuhakan <ubuntuhakan@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 12:00:00 by hozhan            #+#    #+#              #
#    Updated: 2025/06/15 01:35:42 by ubuntuhakan      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

# sources files // will not be wildcard!!
SRCS = $(wildcard *.c)

# object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# default target
all: $(NAME)

# making  archive from objects
$(NAME): $(OBJS)
	$(AR) $@ $^

# compiling rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleaning rules
clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Phony bildirimleri
.PHONY: all bonus clean fclean re