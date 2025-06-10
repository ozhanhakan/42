# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 12:00:00 by hozhan            #+#    #+#              #
#    Updated: 2025/06/10 15:28:36 by hozhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

# Kaynak dosyalar
SRCS = $(wildcard *.c)

# Nesne dosyaları
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Hedefler
all: $(NAME)

# Kütüphane oluşturma
$(NAME): $(OBJS)
	@$(AR) $@ $^

# Derleme kuralı (Norm uyumlu)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


# Temizlik kuralları
clean:
	@$(RM) $(OBJS) 


fclean: clean
	@$(RM) $(NAME)


re: fclean all

# Phony bildirimleri
.PHONY: all bonus clean fclean re