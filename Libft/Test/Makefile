# Test/Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I..
LIBFT = ../libft.a

# Kullanım: make test=ft_strlen_test
ifndef test
$(error "Kullanım: make test=<test_adi> (örnek: make test=ft_strlen_test)")
endif

$(test): $(test).c $(LIBFT)
	@echo "🔨 Derleniyor: $(test).c"
	@$(CC) $(CFLAGS) $(INCLUDES) $(test).c $(LIBFT) -o $(test)
	@echo "🚀 Çalıştırılıyor: ./$(test)"
	@./$(test)

clean:
	@rm -f *_test
	@echo "🧹 Temizlik yapıldı."

.PHONY: clean