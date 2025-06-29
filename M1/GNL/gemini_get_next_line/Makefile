# Dosya Adı: Makefile

# Derleyici ve Derleme Seçenekleri
CC = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

# Programın Adı
NAME = gnl_tester

# Kaynak Dosyalar (.c)
SRCS = get_next_line.c get_next_line_utils.c main.c

# Kaynak dosyalardan üretilecek nesne dosyaları (.o)
OBJS = $(SRCS:.c=.o)

# Başlık Dosyası (.h)
HDR = get_next_line.h

# Ana Kural: Programı derler
all: $(NAME)

# Çalıştırılabilir dosyayı oluşturma kuralı
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# .c dosyalarını .o dosyalarına derleme kuralı
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Temizlik kuralları
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Kural isimlerinin dosya isimleriyle karışmasını önler
.PHONY: all clean fclean re