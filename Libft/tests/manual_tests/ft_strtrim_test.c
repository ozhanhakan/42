#include <stdio.h>   // For printf
#include <stdlib.h>  // For malloc, free
#include <string.h>  // For strcmp, strlen
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_strtrim function prototype (if not in libft.h or commented out)
// char *ft_strtrim(char const *s1, char const *set);
// is_in_set function prototype (if static, declare inside main file or in a separate header)
// static int is_in_set(char c, char const *set); 

// ft_strtrim'in kendi testlerinde kullanmak üzere, standart kütüphane fonksiyonlarıyla
// strtrim'in beklenen davranışını simüle eden bir yardımcı fonksiyon yazmak zor.
// Bunun yerine, her test senaryosunun beklenen çıktısını elle belirleyip karşılaştıracağız.

// --- Yardımcı Test Fonksiyonu ---
void test_strtrim(const char *s1, const char *set, const char *expected_output, const char *description, int test_num)
{
    char *ft_trimmed = NULL;
    int status = 1; // 1 = PASS, 0 = FAIL

    printf("Test %d: %s\n", test_num, description);
    printf("  Original string (s1): \"%s\"\n", s1 ? s1 : "(NULL)");
    printf("  Trim set (set):       \"%s\"\n", set ? set : "(NULL)");
    printf("  Expected output:      \"%s\"\n", expected_output ? expected_output : "(NULL)");

    // Kendi ft_strtrim fonksiyonumuzu çağırıyoruz
    ft_trimmed = ft_strtrim(s1, set);

    // Sonuç kontrolü
    if (expected_output == NULL) // Eğer beklenen çıktı NULL ise (s1 veya set NULL ise)
    {
        if (ft_trimmed != NULL)
        {
            printf("  FAIL: Expected NULL, got non-NULL (%p).\n", (void *)ft_trimmed);
            status = 0;
        }
    }
    else // Eğer beklenen çıktı geçerli bir string ise
    {
        if (ft_trimmed == NULL)
        {
            printf("  FAIL: Expected non-NULL, got NULL.\n");
            status = 0;
        }
        else if (strcmp(ft_trimmed, expected_output) != 0)
        {
            printf("  FAIL: Trimmed string content differs.\n");
            printf("    ft_strtrim output: \"%s\"\n", ft_trimmed);
            status = 0;
        }
        else if (strlen(ft_trimmed) != strlen(expected_output))
        {
            printf("  FAIL: Trimmed string length differs.\n");
            printf("    ft_strtrim length: %zu\n", strlen(ft_trimmed));
            printf("    Expected length:   %zu\n", strlen(expected_output));
            status = 0;
        }
    }

    // Print final status
    printf("  Status: %s\n\n", status ? "GEÇTİ" : "BAŞARISIZ");

    // Free allocated memory to prevent leaks
    if (ft_trimmed)
        free(ft_trimmed);
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_strtrim Testleri ---\n\n");

    // Test 1: Başlangıç ve sondan boşlukları kırpma
    test_strtrim("   Hello World   ", " ", "Hello World", "Basit bosluk kirpma", 1);

    // Test 2: Başka karakterleri kırpma
    test_strtrim("---abc---", "-+", "abc", "Ozel karakter kirpma", 2);

    // Test 3: Stringin ortasındaki karakterler kırpılmamalı
    test_strtrim("___Hello__World___", "_", "Hello__World", "Ortadaki karakterler kirpilmaz", 3);

    // Test 4: String tamamen kırpılıyor (sonuç boş string olmalı)
    test_strtrim("abcabc", "abc", "", "String tamamen kirpiliyor", 4);

    // Test 5: Kırpılacak hiçbir şey yok
    test_strtrim("No trimming needed", "xyz", "No trimming needed", "Kirpilacak sey yok", 5);

    // Test 6: Boş s1 stringi
    test_strtrim("", "abc", "", "Bos s1 stringi", 6);

    // Test 7: Boş set stringi (hiçbir şey kırpılmamalı)
    test_strtrim("  Hello  ", "", "  Hello  ", "Bos set stringi", 7);

    // Test 8: String sadece trim karakterlerinden olusuyor
    test_strtrim("++++", "+", "", "Sadece trim karakterlerinden olusan string", 8);

    // Test 9: s1 NULL ise (beklenen: NULL)
    test_strtrim(NULL, " ", NULL, "s1 NULL", 9);

    // Test 10: set NULL ise (beklenen: NULL)
    test_strtrim("Hello", NULL, NULL, "set NULL", 10);

    // Test 11: s1 ve set NULL ise (beklenen: NULL)
    test_strtrim(NULL, NULL, NULL, "s1 ve set NULL", 11);

    // Test 12: Trim karakterleri stringin ortasında da var
    test_strtrim("xxxabcyzz", "xyz", "abc", "Trim karakterleri ortada", 12);
    
    // Test 13: Tek karakterli s1 ve set
    test_strtrim("a", "a", "", "Tek karakter, tamamen kirpildi", 13);
    test_strtrim("a", "b", "a", "Tek karakter, kirpilmadi", 14);

    return 0;
}
