#include <stdio.h>  // printf için
#include <string.h> // strncmp için
#include <stddef.h> // size_t için
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

// ft_strncmp fonksiyonunun prototipi (eğer libft.h içinde değilse)
// int ft_strncmp(const char *s1, const char *s2, size_t n);

int main(void)
{
    const char *s1_test;
    const char *s2_test;
    size_t n_test;
    int ft_result;
    int std_result;
    
    printf("--- ft_strncmp Testleri ---\n\n");

    // Test 1: Aynı stringler, n tam uzunluk
    s1_test = "hello";
    s2_test = "hello";
    n_test = 5;
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 1: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 2: Aynı stringler, n stringden kısa
    s1_test = "helloworld";
    s2_test = "helloyou";
    n_test = 5; // 'hello' kısmını karşılaştırır
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 2: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 3: Stringler n'den önce farklılaşıyor (ft_result negatif olmalı)
    s1_test = "apple";
    s2_test = "apricot";
    n_test = 4; // 'p' vs 'r'
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 3: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    // Dönüş değerleri tam olarak aynı olmayabilir, ancak işaretleri aynı olmalı (ikisi de negatif veya ikisi de pozitif)
    printf("Durum: %s\n\n", ( (ft_result < 0 && std_result < 0) || (ft_result == std_result) ) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 4: Stringler n'den önce farklılaşıyor (ft_result pozitif olmalı)
    s1_test = "apricot";
    s2_test = "apple";
    n_test = 4; // 'r' vs 'p'
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 4: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", ( (ft_result > 0 && std_result > 0) || (ft_result == std_result) ) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 5: Bir string n'den önce null ile bitiyor (s1 kısa)
    s1_test = "abc";
    s2_test = "abcd";
    n_test = 5; // 'c' ve '\0' karşılaştırılır
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 5: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", ( (ft_result < 0 && std_result < 0) || (ft_result == std_result) ) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 6: Bir string n'den önce null ile bitiyor (s2 kısa)
    s1_test = "abcd";
    s2_test = "abc";
    n_test = 5; // '\0' ve 'c' karşılaştırılır
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 6: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", ( (ft_result > 0 && std_result > 0) || (ft_result == std_result) ) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 7: Boş stringler, n > 0
    s1_test = "";
    s2_test = "";
    n_test = 1;
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 7: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 8: n = 0 durumu
    s1_test = "hello";
    s2_test = "world";
    n_test = 0;
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 8: s1=\"%s\", s2=\"%s\", n=%zu\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // Test 9: Genişletilmiş karakterler (işaretsiz/signed char farkı için önemli)
    // Karakterler signed char olarak yorumlandığında negatif değerler alabilirler.
    // Ancak karşılaştırma sırasında unsigned char'a dönüştürülmeleri gerekir.
    // Örneğin, \xff (255) vs \x01 (1) karşılaştırmasında sonuç pozitif olmalı (254 gibi).
    s1_test = "\xfftest"; // Örneğin: -1 (signed) veya 255 (unsigned)
    s2_test = "\x01test"; // Örneğin: 1
    n_test = 1;
    ft_result = ft_strncmp(s1_test, s2_test, n_test);
    std_result = strncmp(s1_test, s2_test, n_test);
    printf("Test 9: s1=\"%s\", s2=\"%s\", n=%zu (Genişletilmiş Char)\n", s1_test, s2_test, n_test);
    printf("ft_strncmp: %d\n", ft_result);
    printf("strncmp:    %d\n", std_result);
    // Dönüş değerlerinin tam sayısal olarak aynı olması beklenmeyebilir (örneğin 1 vs 254),
    // ancak işaretlerinin aynı olması (ikisi de negatif, ikisi de pozitif veya ikisi de sıfır)
    // fonksiyonun doğru çalıştığını gösterir.
    if ((ft_result == 0 && std_result == 0) ||
        (ft_result < 0 && std_result < 0) ||
        (ft_result > 0 && std_result > 0))
        printf("Durum: GEÇTİ\n\n");
    else
        printf("Durum: BAŞARISIZ\n\n");

    return 0;
}