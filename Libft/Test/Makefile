# Test/Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I..
LIBFT = ../libft.a

# Tüm test dosyalarını otomatik bulma
TEST_SRCS = $(wildcard *_test.c)
TEST_TARGETS = $(TEST_SRCS:_test.c=)

# Varsayılan hedef (tüm testleri listeler)
.PHONY: all
all:
	@echo "Kullanılabilir testler:"
	@for target in $(TEST_TARGETS); do \
		echo "- make $$target"; \
	done

# Dinamik hedef oluşturma (her test için)
define TEST_TEMPLATE
.PHONY: $(1)
$(1): $(1)_test.c $(LIBFT)
	@echo "🔨 Derleniyor: $$<"
	@$(CC) $(CFLAGS) $(INCLUDES) $$< $(LIBFT) -o $$@
	@echo "🚀 Çalıştırılıyor: ./$$@"
	@./$$@
endef

# Her test dosyası için hedef oluştur
$(foreach test,$(TEST_TARGETS),$(eval $(call TEST_TEMPLATE,$(test))))

# Temizleme
.PHONY: clean
clean:
	@rm -f $(TEST_TARGETS)
	@echo "🧹 Çalıştırılabilir dosyalar silindi."