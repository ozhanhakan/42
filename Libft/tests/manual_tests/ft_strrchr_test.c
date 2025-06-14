#include <stdio.h> // printf için
#include <string.h> // strrchr için
#include "../../src/libft.h" // Kendi libft.h dosyanı include etmeyi unutma!

// ft_strrchr fonksiyonunun prototipi (eğer ayrı bir dosyadan gelmiyorsa)
char *ft_strrchr(const char *s, int c); 

int main(void)
{
    const char *str1 = "hello world";
    const char *str2 = "programming";
    const char *str3 = "abcdeabcde";
    const char *str4 = ""; // Boş string
    const char *str5 = "test"; // Null karakter testi için

    char *ft_result;
    char *std_result;
    int c;

    // --- Test Durumu 1: Karakter string içinde birden fazla kez geçiyor ---
    c = 'o';
    ft_result = ft_strrchr(str1, c);
    std_result = strrchr(str1, c);
    printf("Test 1: '%c' in \"%s\"\n", c, str1);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // --- Test Durumu 2: Karakter string içinde tek bir kez geçiyor ---
    c = 'g';
    ft_result = ft_strrchr(str2, c);
    std_result = strrchr(str2, c);
    printf("Test 2: '%c' in \"%s\"\n", c, str2);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // --- Test Durumu 3: Karakter string içinde yok ---
    c = 'z';
    ft_result = ft_strrchr(str3, c);
    std_result = strrchr(str3, c);
    printf("Test 3: '%c' in \"%s\"\n", c, str3);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // --- Test Durumu 4: Boş stringde karakter arama ---
    c = 'a';
    ft_result = ft_strrchr(str4, c);
    std_result = strrchr(str4, c);
    printf("Test 4: '%c' in \"%s\"\n", c, str4);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // --- Test Durumu 5: Null karakter arama (boş string) ---
    c = '\0';
    ft_result = ft_strrchr(str4, c);
    std_result = strrchr(str4, c);
    printf("Test 5: '\\0' in \"%s\"\n", str4);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    // --- Test Durumu 6: Null karakter arama (dolu string) ---
    c = '\0';
    ft_result = ft_strrchr(str5, c);
    std_result = strrchr(str5, c);
    printf("Test 6: '\\0' in \"%s\"\n", str5);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");
    
    // --- Test Durumu 7: İlk karakteri arama ---
    c = 'h';
    ft_result = ft_strrchr(str1, c);
    std_result = strrchr(str1, c);
    printf("Test 7: '%c' in \"%s\"\n", c, str1);
    printf("ft_strrchr: %s (Adres: %p)\n", ft_result ? ft_result : "NULL", (void *)ft_result);
    printf("strrchr:    %s (Adres: %p)\n", std_result ? std_result : "NULL", (void *)std_result);
    printf("Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");


    return 0;
}