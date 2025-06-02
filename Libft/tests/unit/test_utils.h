#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <stdio.h>
# include <stdlib.h> // exit için
# include <string.h> // memcmp için

// Renk tanımlamaları (sabit stringler olarak)
# define GREEN_COLOR "\033[32m"
# define RED_COLOR   "\033[31m"
# define YELLOW_COLOR "\033[33m"
# define RESET_COLOR "\033[0m"

// Test durumu sonuçlarını basar ve başarısızlık durumunda çıkar.
// `test_name` : Testin adı (örn. "ft_memset basic fill")
// `success`   : Test başarılıysa 1, başarısızsa 0
void    report_test_status(const char *test_name, int success);

// Bellek bloklarını karşılaştırır ve eğer farklıysa hata mesajı basar.
// `s1`        : İlk bellek bloğu
// `s2`        : İkinci bellek bloğu
// `n`         : Karşılaştırılacak byte sayısı
// `message`   : Hata durumunda basılacak açıklayıcı mesaj
// Dönüş: Eşitse 1, farklıysa 0
int     check_memory_equality(const void *s1, const void *s2, size_t n, const char *message);

// Bir test fonksiyonunu çalıştırır ve sonucunu raporlar.
// `test_func`     : Çalıştırılacak test fonksiyonunun pointer'ı (0 başarılı, 1 başarısız döndürmeli)
// `test_func_name`: Çalıştırılan test fonksiyonunun adı (örn. "ft_memset_test")
void    run_test_suite(int (*test_func)(), const char *test_func_name);

// Yardımcı fonksiyon: Testlerin başında ve sonunda başlık basar.
void    print_suite_header(const char *suite_name);
void    print_suite_footer(const char *suite_name, int success);

#endif