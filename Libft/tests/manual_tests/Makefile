# Libft Test Makefile (tests/manual_tests/Makefile)
# Bu Makefile, 'make <test_dosya_adı>' komutuyla tekil test dosyalarını derlemenizi sağlar.
# Ayrıca, test derlemesinden önce ana libft.a kütüphanesini otomatik olarak günceller.

# --- KONFİGÜRASYON ---
# Derleyici bayrakları
CFLAGS = -Wall -Wextra -Werror -g # -g hata ayıklama sembolleri için

# Ana libft proje dizininin yolu.
# Bu Makefile'ın 'tests/manual_tests' gibi bir alt dizinde olduğunu varsayar.
# Eğer 'src' klasörünüz bu Makefile'a göre farklı bir yoldaysa, ayarlamanız gerekir.
LIBFT_SRC_DIR = ../../src 

# Kütüphane dosyası detayları
LIBFT_ARCHIVE_NAME = libft.a
LIBFT_ARCHIVE_PATH = $(LIBFT_SRC_DIR)/$(LIBFT_ARCHIVE_NAME)

# Libft için bağlayıcı (linker) kütüphane flag'leri
# Make'in dahili kurallarında kullanılan LDLIBS, genellikle kütüphaneleri sona ekler.
LDLIBS = -L$(LIBFT_SRC_DIR) -lft

# Standart C derleyici ve silme komutu
CC = cc
RM = rm -f

# Bu dizindeki tüm .c test dosyalarını otomatik olarak bulur.
TEST_SRCS = $(wildcard *.c)
# Her test .c dosyası için oluşturulacak çalıştırılabilir dosya adları.
TEST_EXES = $(TEST_SRCS:.c=)
# Her test .c dosyası için oluşturulacak object dosya adları.
TEST_OBJS = $(TEST_SRCS:.c=.o)

# --- PHONY HEDEFLER ---
# .PHONY, bu hedeflerin gerçek bir dosya olmadığını, sadece komut takma adları olduğunu belirtir.
.PHONY: all clean fclean re force_libft_rebuild $(TEST_EXES)

# --- VARSAYILAN HEDEF ---
# 'make' argümansız çalıştırılırsa, tüm test çalıştırılabilirlerini derler.
all: $(TEST_EXES)

# --- BAĞIMLILIKLAR VE KURALLAR ---

# libft.a'nın güncel olduğundan emin olmak için kural.
# force_libft_rebuild phony hedefi sayesinde, bu kural her zaman tetiklenecek
# ve dolayısıyla src/Makefile her zaman kontrol edilecek.
$(LIBFT_ARCHIVE_PATH): force_libft_rebuild
	@echo "--- $(LIBFT_ARCHIVE_NAME) güncelleniyor: $(LIBFT_SRC_DIR) ---"
	# libft.a'yı temizleyip baştan derlemek için 'make re' kullanıyoruz.
	make -C $(LIBFT_SRC_DIR) re 
	@echo "--- $(LIBFT_ARCHIVE_NAME) güncel. ---"

# force_libft_rebuild hedefi: Her zaman tetiklenir, libft.a bağımlılığını zorlar.
force_libft_rebuild:

# Tüm test çalıştırılabilirleri, libft.a'nın güncel olmasına bağlıdır.
$(TEST_EXES): $(LIBFT_ARCHIVE_PATH)

# Test çalıştırılabilir dosyalarını derlemek için kalıp kuralı.
# Örneğin, 'ft_strrchr_test' için 'ft_strrchr_test.o'ya bağlıdır.
# Bu kural, make'in built-in kurallarını aşmak için yeterince açık olmalıdır.
$(TEST_EXES): %: %.o
	@echo "--- $@ bağlanıyor ---"
	# $<: hedefin ilk önkoşulu (yani .o dosyası)
	# $@: hedefin adı (yani çalıştırılabilir dosya)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS) 
	@echo "--- Çalıştırılabilir '$@' oluşturuldu. ---"

# .c dosyalarını .o dosyalarına derlemek için kalıp kuralı.
# Her test .c dosyası, kendi .o dosyasını oluşturur.
%.o: %.c
	@echo "--- $< derleniyor ---"
	$(CC) $(CFLAGS) -c $< -o $@

# --- TEMİZLEME KURALLARI ---

# clean kuralı: Bu Makefile tarafından oluşturulan tüm object dosyalarını (*.o) siler.
clean:
	@echo "--- Test object dosyaları temizleniyor (*.o)... ---"
	$(RM) $(TEST_OBJS)

# fclean kuralı: Tüm object dosyalarını (*.o) VE tüm test çalıştırılabilirlerini siler.
fclean: clean
	@echo "--- Test çalıştırılabilirleri temizleniyor... ---"
	$(RM) $(TEST_EXES)

# re kuralı: fclean çalıştırır ve ardından 'all' hedefini tekrar derler.
re: fclean all
