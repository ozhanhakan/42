# Libft Test Makefile (tests/manual_tests/Makefile) - GÜNCELLENMİŞ VERSİYON
# Bu Makefile, 'make <test_dosya_adı>' komutuyla tekil test dosyalarını derler.
# Ana libft.a kütüphanesini yalnızca gerektiğinde günceller.

# --- KONFİGÜRASYON ---
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

# Ana libft proje dizininin ve kütüphane dosyasının yolları.
LIBFT_SRC_DIR = ../../src
LIBFT_ARCHIVE_NAME = libft.a
LIBFT_ARCHIVE_PATH = $(LIBFT_SRC_DIR)/$(LIBFT_ARCHIVE_NAME)

# Bağlayıcı (linker) kütüphane flag'leri.
LDLIBS = -L$(LIBFT_SRC_DIR) -lft

# Bu dizindeki tüm test kaynaklarını, obje dosyalarını ve çalıştırılabilir dosyaları otomatik olarak bulur.
TEST_SRCS = $(wildcard *.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_EXES = $(TEST_SRCS:.c=)

# --- PHONY HEDEFLER ---
# Bu hedeflerin gerçek bir dosya olmadığını belirtir.
.PHONY: all bonus clean fclean re $(TEST_EXES)

# --- VARSAYILAN HEDEF ---
# 'make' argümansız çalıştırılırsa, tüm test çalıştırılabilirlerini derler.
all: $(TEST_EXES)

# --- BAĞIMLILIKLAR VE KURALLAR ---

# libft.a'nın güncel olduğundan emin olmak için kural.
# Bu kural, bir test dosyası derlenmeden önce çalışır.
# ÖNEMLİ DEĞİŞİKLİK: 'force_libft_rebuild' kaldırıldı. Artık make, src dizinindeki
# dosyaların zaman damgalarını kontrol ederek GEREKTİĞİNDE derleme yapacak.
$(LIBFT_ARCHIVE_PATH):
	@echo "--- libft.a kontrol ediliyor ve gerekirse güncelleniyor: $(LIBFT_SRC_DIR) ---"
	# 're' yerine 'all' (veya sadece 'make') kullanıyoruz.
	# Bu, gereksiz yeniden derlemeleri önler.
	@$(MAKE) -C $(LIBFT_SRC_DIR) bonus

# Tüm test çalıştırılabilirleri, libft.a'nın güncel olmasına bağlıdır.
$(TEST_EXES): $(LIBFT_ARCHIVE_PATH)

# Test çalıştırılabilir dosyalarını derlemek için kalıp kuralı.
# Örn: 'make ft_putendl_fd_test' bu kuralı kullanır.
# Bu kural yapısı, her bir test için ayrı ayrı hedef yazma ihtiyacını ortadan kaldırır.
$(TEST_EXES): %: %.o
	@echo "--- '$@' çalıştırılabilir dosyası bağlanıyor ---"
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)
	@echo "--- '$@' oluşturuldu. ---"

# .c dosyalarını .o dosyalarına derlemek için kalıp kuralı.
%.o: %.c
	@echo "--- '$<' kaynak dosyası derleniyor ---"
	$(CC) $(CFLAGS) -c $< -o $@

# --- TEMİZLEME KURALLARI ---

# clean: Bu dizindeki obje dosyalarını (*.o) siler.
clean:
	@echo "--- Test object dosyaları temizleniyor (*.o)... ---"
	@$(RM) $(TEST_OBJS)

# fclean: clean kuralına ek olarak, test çalıştırılabilirlerini VE ana libft.a'yı siler.
fclean: clean
	@echo "--- Test çalıştırılabilirleri temizleniyor... ---"
	@$(RM) $(TEST_EXES)
	@echo "--- Ana kütüphane temizleniyor (libft.a)... ---"
	# DEĞİŞİKLİK: libft.a'yı silmek için src'deki 'fclean' kuralını çağırıyoruz.
	@$(MAKE) -C $(LIBFT_SRC_DIR) fclean

# re: Her şeyi temizler ve baştan derler.
re: fclean all