#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // malloc, free gibi bellek yönetimi fonksiyonları için gerekli
# include <unistd.h> // read fonksiyonu için gerekli

// BUFFER_SIZE makrosu, okuma işlemlerinde kullanılacak buffer boyutunu belirler.
// Eğer derleyiciye -D BUFFER_SIZE=xx parametresi verilmezse, burada varsayılan olarak 42 atanır.
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// get_next_line fonksiyonu, verilen dosya tanımlayıcısından (fd) bir satır okur ve döndürür.
char	*get_next_line(int fd);

// Yardımcı fonksiyonlar:
// ft_strchr: Bir karakterin string içinde olup olmadığını bulur.
char	*ft_strchr(const char *s, int c);
// ft_strdup: Bir stringin kopyasını oluşturur.
char	*ft_strdup(const char *s);
// ft_strjoin_and_free: İki stringi birleştirir, ilkini serbest bırakır.
char	*ft_strjoin_and_free(char *s1, char *s2);
// ft_strlen: String uzunluğunu döndürür.
size_t	ft_strlen(const char *s);

#endif
