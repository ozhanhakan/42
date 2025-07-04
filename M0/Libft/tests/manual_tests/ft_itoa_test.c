#include <stdio.h>    // For printf
#include <stdlib.h>   // For atoi, free, itoa (if available, usually not standard)
#include <string.h>   // For strcmp
#include <limits.h>   // For INT_MIN, INT_MAX
#include "../../src/libft.h"  // Don't forget to include your libft.h here!

// ft_itoa function prototype (if not in libft.h or commented out)
// char *ft_itoa(int n);

// Helper function to compare ft_itoa output with standard behavior
void test_itoa(int n, const char *description, int test_num)
{
    char *ft_str = NULL;
    char std_str_buffer[20]; // Yeterince büyük bir tampon (INT_MIN için yeterli)
    const char *expected_str;
    int status = 1; // 1 = PASS, 0 = FAIL

    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Input integer: %d\n", n);

    // Kendi ft_itoa fonksiyonumuzu çağırıyoruz
    ft_str = ft_itoa(n);

    // Standart itoa'nın çıktısını elde ediyoruz (sprintf kullanarak daha evrensel)
    sprintf(std_str_buffer, "%d", n);
    expected_str = std_str_buffer;

    printf("  Expected string: \"%s\"\n", expected_str);
    printf("  ft_itoa output:  \"%s\"\n", ft_str ? ft_str : "(NULL)");

    // Sonuçları karşılaştır
    if (ft_str == NULL) // Tahsis başarısız olursa
    {
        printf("  FAIL: ft_itoa returned NULL.\n");
        status = 0;
    }
    else if (strcmp(ft_str, expected_str) != 0) // String içerikleri farklıysa
    {
        printf("  FAIL: String content mismatch.\n");
        status = 0;
    }
    else
    {
        printf("  String content matches.\n");
    }

    // Print final status
    printf("  Overall Status: %s\n\n", status ? "GEÇTİ" : "BAŞARISIZ");

    // Free allocated memory
    if (ft_str)
        free(ft_str);
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_itoa Testleri ---\n\n");

    // Test 1: Pozitif sayılar
    test_itoa(0, "Sıfır", 1);
    test_itoa(1, "Pozitif tek basamaklı", 2);
    test_itoa(123, "Pozitif çok basamaklı", 3);
    test_itoa(100, "Pozitif sonu sıfırlı", 4);
    test_itoa(987654321, "Pozitif büyük sayı", 5);

    // Test 6: Negatif sayılar
    test_itoa(-1, "Negatif tek basamaklı", 6);
    test_itoa(-123, "Negatif çok basamaklı", 7);
    test_itoa(-100, "Negatif sonu sıfırlı", 8);
    test_itoa(-987654321, "Negatif büyük sayı", 9);

    // Test 10: Sınır değerleri
    test_itoa(INT_MAX, "INT_MAX", 10); // Genellikle 2147483647
    test_itoa(INT_MIN, "INT_MIN", 11); // Genellikle -2147483648

    // Bellek tahsisi başarısızlığı durumu (simüle edilemez, sadece mantık olarak kontrol edilebilir)
    // Bu tür testler için Mock malloc kullanmak gerekir, Libft için bu seviyede test yapmayız.

    return 0;
}
