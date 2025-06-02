# Renkler
GREEN	:= \033[32m
RED		:= \033[31m
YELLOW	:= \033[33m
RESET	:= \033[0m

# Derleyici ayarları
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I./src # src dizinini include path'e ekledik
LDFLAGS	= -Lsrc -lft # Linker flag'lerini ayrı bir değişkende tut

# Varsayılan hedef
.DEFAULT_GOAL := all

# Libft derleme
all: src/libft.a
	@echo "$(GREEN)✓ libft.a created$(RESET)"

bonus: src/libft.a_bonus
	@echo "$(GREEN)✓ libft.a (with bonuses) created$(RESET)"

# libft.a ve bonuslu libft.a'yı src makefile'ından derlemek için kurallar
src/libft.a:
	@$(MAKE) -C src all

src/libft.a_bonus:
	@$(MAKE) -C src bonus

# Testler için genel değişkenler
TEST_DIR = tests/unit
TEST_UTILS_SRC = $(TEST_DIR)/test_utils.c
TEST_UTILS_OBJ = $(TEST_UTILS_SRC:.c=.o)

# Tüm test binary'leri için bir pattern
TEST_BIN_PREFIX = $(TEST_DIR)/
TEST_BIN_SUFFIX = _test

# `test-ft_abc` hedefi için genel kural
# Bu kurala özel değişken tanımlamaları yapabiliriz.
test-%: bonus $(TEST_UTILS_OBJ)
	@echo "$(YELLOW)=== Running Test: $* ===$(RESET)"
	# Test kaynak dosyasının tam yolu
	# makefile değişkenleri bu şekilde tanımlanır.
	$(eval TEST_SRC_FILE = $(TEST_DIR)/$*_test.c)
	# Test binary'sinin tam yolu
	$(eval TEST_BINARY = $(TEST_BIN_PREFIX)$*$(TEST_BIN_SUFFIX))

	@if [ ! -f $(TEST_SRC_FILE) ]; then \
		echo "$(RED)Error: Test file $(TEST_SRC_FILE) not found!$(RESET)"; \
		exit 1; \
	fi

	# Test binary'sini derle
	# make değişkenlerini $(VAR_NAME) şeklinde kullanıyoruz
	$(CC) $(CFLAGS) $(TEST_SRC_FILE) $(TEST_UTILS_OBJ) $(LDFLAGS) -o $(TEST_BINARY)

	# Derleme başarılı olursa test binary'sini çalıştır
	@echo "$(YELLOW)Executing $(TEST_BINARY)...$(RESET)"
	@./$(TEST_BINARY) || (echo "$(RED)Test $(TEST_BINARY) FAILED!$(RESET)" && rm -f $(TEST_BINARY) && exit 1)
	@echo "$(GREEN)Test $(TEST_BINARY) COMPLETED.$(RESET)"
	@rm -f $(TEST_BINARY) # Test binary'sini temizle


# test_utils.c için derleme kuralı (tek seferlik derlenir)
$(TEST_UTILS_OBJ): $(TEST_UTILS_SRC)
	@echo "$(YELLOW)Compiling $(TEST_UTILS_SRC)...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Valgrind testleri
valgrind-%: bonus $(TEST_UTILS_OBJ)
	@echo "$(YELLOW)=== VALGRIND CHECK FOR $* ===$(RESET)"
	$(eval TEST_SRC_FILE = $(TEST_DIR)/$*_test.c)
	$(eval TEST_BINARY = $(TEST_BIN_PREFIX)$*$(TEST_BIN_SUFFIX))

	@if [ ! -f $(TEST_SRC_FILE) ]; then \
		echo "$(RED)Error: Test file $(TEST_SRC_FILE) not found!$(RESET)"; \
		exit 1; \
	fi
	
	$(CC) $(CFLAGS) $(TEST_SRC_FILE) $(TEST_UTILS_OBJ) $(LDFLAGS) -o $(TEST_BINARY)
	
	@echo "$(YELLOW)Running Valgrind on $(TEST_BINARY)...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	./$(TEST_BINARY) 2>&1 | tee valgrind_report_$*.txt
	@grep -q "LEAK SUMMARY: 0 bytes in 0 contexts" valgrind_report_$*.txt && \
	echo "$(GREEN)Valgrind clean for $*! No leaks found.$(RESET)" || \
	echo "$(RED)Valgrind found issues for $*! Check valgrind_report_$*.txt$(RESET)"
	@rm -f $(TEST_BINARY)
	@rm -f valgrind_report_$*.txt # Raporu istersen tutabilirsin

# Temizlik
clean:
	@$(MAKE) -C src clean
	@$(RM) $(TEST_UTILS_OBJ)
	@$(RM) $(TEST_DIR)/*$(TEST_BIN_SUFFIX)
	@echo "$(YELLOW)Object files and test binaries removed$(RESET)"

fclean: clean
	@$(MAKE) -C src fclean
	@echo "$(YELLOW)libft.a and all test binaries removed$(RESET)"

re: fclean all

.PHONY: all bonus test test-% valgrind-% clean fclean re