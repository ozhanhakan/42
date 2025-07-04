#include <stdio.h>   // For printf
#include <stdlib.h>  // For free
#include <string.h>  // For strcmp, strlen
#include <ctype.h>   // For tolower, toupper (test helper functions)
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_strmapi function prototype (if not in libft.h or commented out)
// char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

// --- Test için yardımcı callback fonksiyonları ---

// Her karakteri büyük harfe dönüştüren callback
char my_toupper(unsigned int i, char c)
{
    (void)i; // 'i' kullanılmadığı için "unused parameter" uyarısını engellemek için
    if (c >= 'a' && c <= 'z')
        return (c - 32); // ASCII farkı 'a'-'A' = 32
    return (c);
}

// Her karakteri küçük harfe dönüştüren callback
char my_tolower(unsigned int i, char c)
{
    (void)i;
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

// Karakterin indeksine göre değiştiren callback
// Çift indeksli karakterleri büyük harfe, tek indekslileri küçük harfe dönüştürür.
char capitalize_even_index(unsigned int i, char c)
{
    if (i % 2 == 0) // Çift indeks
    {
        if (c >= 'a' && c <= 'z')
            return (c - 32);
    }
    else // Tek indeks
    {
        if (c >= 'A' && c <= 'Z')
            return (c + 32);
    }
    return (c);
}

// --- Yardımcı Test Fonksiyonu ---
void test_strmapi(const char *s, char (*f)(unsigned int, char), const char *expected_output, const char *description, int test_num)
{
    char *ft_result = NULL;
    int status = 1; // 1 = PASS, 0 = FAIL

    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Original string (s): \"%s\"\n", s ? s : "(NULL)");
    printf("  Expected output:       \"%s\"\n", expected_output ? expected_output : "(NULL)");

    // Kendi ft_strmapi fonksiyonumuzu çağırıyoruz
    ft_result = ft_strmapi(s, f);

    printf("  ft_strmapi output:     \"%s\"\n", ft_result ? ft_result : "(NULL)");

    // Sonuçları karşılaştır
    if (expected_output == NULL) // Eğer beklenen çıktı NULL ise (s veya f NULL ise)
    {
        if (ft_result != NULL)
        {
            printf("  FAIL: Expected NULL, got non-NULL (%p).\n", (void *)ft_result);
            status = 0;
        }
    }
    else // Eğer beklenen çıktı geçerli bir string ise
    {
        if (ft_result == NULL)
        {
            printf("  FAIL: Expected non-NULL, got NULL.\n");
            status = 0;
        }
        else if (strcmp(ft_result, expected_output) != 0) // String içerikleri farklıysa
        {
            printf("  FAIL: String content mismatch.\n");
            status = 0;
        }
        else if (strlen(ft_result) != strlen(expected_output)) // Uzunluk farklıysa
        {
            printf("  FAIL: String length mismatch.\n");
            status = 0;
        }
    }

    // Print final status
    printf("  Overall Status: %s\n\n", status ? "GEÇTİ" : "BAŞARISIZ");

    // Free allocated memory
    if (ft_result)
        free(ft_result);
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_strmapi Testleri ---\n\n");

    // Test 1: Basit büyük harfe dönüştürme
    test_strmapi("hello world", my_toupper, "HELLO WORLD", "Basit buyuk harfe donusturme", 1);

    // Test 2: Basit küçük harfe dönüştürme
    test_strmapi("HELLO WORLD", my_tolower, "hello world", "Basit kucuk harfe donusturme", 2);

    // Test 3: Boş string
    test_strmapi("", my_toupper, "", "Bos string", 3);

    // Test 4: Sadece sayılar ve semboller
    test_strmapi("123!@#", my_toupper, "123!@#", "Sayilar ve semboller", 4);

    // Test 5: İndeks bazlı dönüştürme
    test_strmapi("AbcDeFg", capitalize_even_index, "ABCdefG", "Indeks bazli donusturme", 5);

    // Test 6: S NULL ise (beklenen: NULL)
    test_strmapi(NULL, my_toupper, NULL, "s NULL", 6);

    // Test 7: f NULL ise (beklenen: NULL)
    test_strmapi("hello", NULL, NULL, "f NULL", 7);

    // Test 8: S ve f NULL ise (beklenen: NULL)
    test_strmapi(NULL, NULL, NULL, "s ve f NULL", 8);
    
    // Test 9: Sadece bir karakter
    test_strmapi("x", my_toupper, "X", "Tek karakter", 9);

    return 0;
}

