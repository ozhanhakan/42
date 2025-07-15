# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/13 17:00:00 by hozhan            #+#    #+#              #
#    Updated: 2025/07/15 17:11:49 by hozhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -f

# Source files
SRCS = ft_printf.c \
       ft_printf_handlers_1.c \
       ft_printf_handlers_2.c \
       ft_printf_str_utils.c \
	   ft_printf_num_utils.c 

# Object files
OBJS = $(SRCS:.c=.o)

# Header file
HEADER = ft_printf.h

# Colors for output (optional - görsel feedback için)
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Default target - make komutu çalıştırıldığında bu hedef çalışır
all: $(NAME)

# Library creation rule
# Static library (.a) oluşturmak için object files'ları archive et
$(NAME): $(OBJS)
	@echo "$(BLUE)Creating library $(NAME)...$(RESET)"
	$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✓ Library $(NAME) created successfully!$(RESET)"

# Object file compilation rule
# Pattern rule: .c files'ları .o files'lara çevir
%.o: %.c $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Removing object files...$(RESET)"
	$(RM) $(OBJS)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

# Clean everything (objects + library)
fclean: clean
	@echo "$(RED)Removing library $(NAME)...$(RESET)"
	$(RM) $(NAME)
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

# Rebuild everything from scratch
re: fclean all

# Test target (optional - development için)
test: $(NAME)
	@echo "$(BLUE)Compiling test program...$(RESET)"
	$(CC) $(CFLAGS) test_main.c -L. -lftprintf -o test_printf
	@echo "$(GREEN)✓ Test program compiled! Run with: ./test_printf$(RESET)"

# Norminette check (42 coding standard)
norm:
	@echo "$(BLUE)Checking norminette...$(RESET)"
	norminette $(SRCS) $(HEADER)

# Install rule (system-wide installation - optional)
install: $(NAME)
	@echo "$(BLUE)Installing library...$(RESET)"
	cp $(NAME) /usr/local/lib/
	cp $(HEADER) /usr/local/include/
	@echo "$(GREEN)✓ Library installed to system!$(RESET)"

# Uninstall rule
uninstall:
	@echo "$(RED)Uninstalling library...$(RESET)"
	$(RM) /usr/local/lib/$(NAME)
	$(RM) /usr/local/include/$(HEADER)
	@echo "$(GREEN)✓ Library uninstalled!$(RESET)"

# Help target - kullanım bilgileri
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)       - Build the library"
	@echo "  $(GREEN)clean$(RESET)     - Remove object files"  
	@echo "  $(GREEN)fclean$(RESET)    - Remove object files and library"
	@echo "  $(GREEN)re$(RESET)        - Rebuild everything"
	@echo "  $(GREEN)test$(RESET)      - Build test program"
	@echo "  $(GREEN)norm$(RESET)      - Check norminette compliance"
	@echo "  $(GREEN)install$(RESET)   - Install library system-wide"
	@echo "  $(GREEN)uninstall$(RESET) - Remove library from system"

# Phony targets (bu hedefler dosya oluşturmaz)
.PHONY: all clean fclean re test norm install uninstall help

# Makefile Usage Instructions:
#
# 1. Build library:
#    make
#    
# 2. Clean temporary files:
#    make clean
#    
# 3. Full clean:
#    make fclean
#    
# 4. Rebuild:
#    make re
#    
# 5. Test:
#    make test
#    
# 6. Check coding standards:
#    make norm
#
# Library Integration:
#
# 1. In your project Makefile:
#    CC = gcc
#    CFLAGS = -Wall -Wextra -Werror
#    LIBS = -L./path/to/libftprintf -lftprintf
#    
#    your_program: your_files.o
#    	$(CC) $(CFLAGS) your_files.o $(LIBS) -o your_program
#
# 2. In your source code:
#    #include "ft_printf.h"
#    
#    int main() {
#        ft_printf("Hello %s! Number: %d\n", "World", 42);
#        return (0);
#    }
