# Derleyici ve flag'ler
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

# Kaynak dosyalar ve object dosyaları
SRCS_DIR = srcs
SRCS = $(wildcard $(SRCS_DIR)/*.c)  # srcs dizinindeki tüm .c dosyalarını bul
OBJS = $(SRCS:.c=.o)

# Kütüphane adı
NAME = libft.a

# Varsayılan hedef
all: $(NAME)

# Kütüphane oluşturma kuralı
$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Object dosyalarını derleme kuralı
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Temizleme kuralları
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# Yeniden derleme kuralı
re: fclean all

# Phony hedefler
.PHONY: all clean fclean re