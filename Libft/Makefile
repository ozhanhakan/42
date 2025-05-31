# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 12:00:00 by hozhan            #+#    #+#              #
#    Updated: 2025/06/01 01:24:39 by hozhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Renkler
GREEN	:= \033[32m
RED		:= \033[31m
YELLOW	:= \033[33m
RESET	:= \033[0m

# Derleyici ayarları
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# Varsayılan hedef
.DEFAULT_GOAL := all

# Libft derleme
all:
	@make -C src
	@echo "$(GREEN)✓ libft.a created$(RESET)"

bonus:
	@make -C src bonus
	@echo "$(GREEN)✓ libft.a (with bonuses) created$(RESET)"

# Unit testler
test: bonus
	@echo "$(YELLOW)=== UNIT TESTS ===$(RESET)"
	@for test in tests/unit/*_test.c; do \
		test_name=$$(basename $$test .c); \
		$(CC) $(CFLAGS) -Isrc -Lsrc -lft $$test -o $$test_name && \
		./$$test_name || exit 1; \
		rm -f $$test_name; \
	done

# Test derleme kuralı
test-%: bonus
	@echo "$(YELLOW)Testing $*$(RESET)"
	@$(CC) $(CFLAGS) -Isrc tests/unit/$*_test.c tests/unit/test_utils.c -Lsrc -lft -o tests/unit/$*_test
	@cd tests/unit && ./$*_test || (rm -f $*_test && exit 1)
	@rm -f tests/unit/$*_test
	
# Valgrind testleri
valgrind: bonus
	@echo "$(YELLOW)=== VALGRIND CHECK ===$(RESET)"
	@for test in tests/unit/*_test.c; do \
		test_name=$$(basename $$test .c); \
		$(CC) $(CFLAGS) -Isrc -Lsrc -lft $$test -o $$test_name && \
		valgrind --leak-check=full --show-leak-kinds=all \
		./$$test_name 2>&1 | grep -A5 "LEAK SUMMARY"; \
		rm -f $$test_name; \
	done

# Temizlik
clean:
	@make -C src clean
	@echo "$(YELLOW)Object files removed$(RESET)"

fclean: clean
	@make -C src fclean
	@rm -f *_test
	@echo "$(YELLOW)libft.a and test binaries removed$(RESET)"

re: fclean all

.PHONY: all bonus test test-% valgrind clean fclean re