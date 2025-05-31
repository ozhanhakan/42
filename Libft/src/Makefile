# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 12:00:00 by hozhan            #+#    #+#              #
#    Updated: 2025/05/31 23:22:53 by hozhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

# Mandatory sources (bonus hariç)
SRCS = $(filter-out %_bonus.c,$(wildcard *.c))
BONUS_SRCS = $(wildcard *_bonus.c)

# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Primary targets
all: $(NAME)

bonus: $(BONUS_OBJS)
	@make OBJS="$(OBJS) $(BONUS_OBJS)" $(NAME)
	@echo "\033[32m✓ Bonus functions added to $(NAME)\033[0m"

# Library creation (no relinking)
$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "\033[32m✓ $@ created\033[0m"

# Compilation rule (Norm compliant)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[33mCompiling $<\033[0m"

# Clean rules
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "\033[33mObject files removed\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[33m$(NAME) removed\033[0m"

re: fclean all

# Phony declarations
.PHONY: all bonus clean fclean re