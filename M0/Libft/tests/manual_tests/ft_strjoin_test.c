#include <stdio.h>   // For printf
#include <stdlib.h>  // For malloc, free
#include <string.h>  // For strcmp, strlen, strdup (for standard join)
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_strjoin function prototype (if not in libft.h or commented out)
// char    *ft_strjoin(char const *s1, char const *s2);

// --- Yardımcı Test Fonksiyonu ---
void test_strjoin(const char *s1, const char *s2, const char *description, int test_num)
{
    char *ft_joined = NULL;
    char *std_joined = NULL; // Standard strdup ile manuel birleştirme yapacağız
    int status = 1; // 1 = PASS, 0 = FAIL

    printf("Test %d: %s\n", test_num, description);
    printf("  s1: \"%s\"\n", s1 ? s1 : "(NULL)");
    printf("  s2: \"%s\"\n", s2 ? s2 : "(NULL)");

    // Kendi ft_strjoin fonksiyonumuzu çağırıyoruz
    ft_joined = ft_strjoin(s1, s2);

    // Standart string birleştirmeyi manuel olarak simüle ediyoruz
    // Bu, std_strjoin olmadığı için geçici bir yaklaşımdır.
    if (!s1 || !s2) // Eğer s1 veya s2 NULL ise, standart strdup veya strcat kullanılamaz.
    {
        std_joined = NULL; // NULL girdide beklenen NULL dönüş
    }
    else
    {
        // Yeterli bellek tahsis et
        size_t len_s1 = strlen(s1);
        size_t len_s2 = strlen(s2);
        std_joined = (char *)malloc(len_s1 + len_s2 + 1);
        if (std_joined)
        {
            strcpy(std_joined, s1); // İlk stringi kopyala
            strcat(std_joined, s2); // İkinci stringi ekle
        }
    }


    // Bellek tahsisi ve sonuç kontrolü
    if ((ft_joined == NULL && std_joined != NULL) || (ft_joined != NULL && std_joined == NULL))
    {
        printf("  FAIL: Allocation status differs.\n");
        status = 0;
    }
    else if (ft_joined == NULL && std_joined == NULL)
    {
        printf("  Allocation FAILED for both functions (expected).\n");
        printf("  Status: PASS\n\n");
        return;
    }
    else // Both allocated successfully, now check content
    {
        if (strcmp(ft_joined, std_joined) != 0)
        {
            printf("  FAIL: Joined string content differs.\n");
            printf("    ft_strjoin output: \"%s\"\n", ft_joined);
            printf("    Std joined output: \"%s\"\n", std_joined);
            status = 0;
        }
        else
        {
            printf("  Joined string content matches.\n");
        }
    }

    // Print final status
    printf("  Status: %s\n\n", status ? "PASS" : "FAIL");

    // Free allocated memory to prevent leaks
    if (ft_joined)
        free(ft_joined);
    if (std_joined)
        free(std_joined);
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_strjoin Testleri ---\n\n");

    // Test 1: Temel birleştirme
    test_strjoin("Hello", "World", "Basit birleştirme", 1);

    // Test 2: İlk string boş
    test_strjoin("", "World", "İlk string boş", 2);

    // Test 3: İkinci string boş
    test_strjoin("Hello", "", "İkinci string boş", 3);

    // Test 4: Her iki string de boş
    test_strjoin("", "", "Her iki string de boş", 4);

    // Test 5: Uzun stringler
    test_strjoin("Lorem ipsum dolor sit amet, consectetur", "adipiscing elit, sed do eiusmod tempor.", "Uzun string birleştirme", 5);

    // Test 6: İlk string NULL (davranışı tanımlı olmalı: NULL dönmeli)
    test_strjoin(NULL, "World", "İlk string NULL", 6);

    // Test 7: İkinci string NULL (davranışı tanımlı olmalı: NULL dönmeli)
    test_strjoin("Hello", NULL, "İkinci string NULL", 7);

    // Test 8: Her iki string de NULL (davranışı tanımlı olmalı: NULL dönmeli)
    test_strjoin(NULL, NULL, "Her iki string de NULL", 8);

    return 0;
}
