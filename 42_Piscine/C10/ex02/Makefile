# Programın adı
NAME = ft_tail

# Derleyici ve derleme ayarları
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes

# Kaynak dosyalar ve bunlardan türetilecek nesne dosyaları
SRC_DIR = src
SRC_FILES = ft_tail.c ft_utils.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

# Varsayılan hedef
all: $(NAME)

# Nesne dosyalarını oluşturma kuralları
$(OBJ): %.o: %.c includes/ft_tail.h
	$(CC) $(CFLAGS) -c $< -o $@

# Çalıştırılabilir dosyayı oluşturma
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Geçici dosyaları temizleme
clean:
	rm -f $(OBJ)

# Tüm derlenen dosyaları temizleme
fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean