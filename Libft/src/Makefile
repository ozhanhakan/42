# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 12:00:00 by hozhan            #+#    #+#              #
#    Updated: 2025/06/02 15:16:37 by hozhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

# Kaynak dosyalar
SRCS = $(filter-out %_bonus.c,$(wildcard *.c))
BONUS_SRCS = $(wildcard *_bonus.c)

# Nesne dosyaları
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Hedefler
all: $(NAME)

# bonus hedefi, bonuslu nesne dosyalarını da kullanarak libft.a'yı yeniden oluşturur.
# Kök makefile'dan çağrıldığında, OBJS değişkenini geçerek tüm nesneleri derler.
bonus: $(OBJS) $(BONUS_OBJS)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "\033[32m✓ Bonus functions added to $(NAME)\033[0m"

# Kütüphane oluşturma
$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "\033[32m✓ $@ created\033[0m"

# Derleme kuralı (Norm uyumlu)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[33mCompiling $<\033[0m"

# Temizlik kuralları
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "\033[33mObject files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[33m$(NAME) removed$(RESET)"

re: fclean all

# Phony bildirimleri
.PHONY: all bonus clean fclean re