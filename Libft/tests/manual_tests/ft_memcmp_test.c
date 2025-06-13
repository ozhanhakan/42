#include <stdio.h>
#include <string.h>

// Senin ft_memcmp kodun
int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *ptr1;
    const unsigned char *ptr2;

    if (n == 0)
        return (0);
    ptr1 = (const unsigned char *)s1;
    ptr2 = (const unsigned char *)s2;
    while (n)
    {
        if (*ptr1 != *ptr2)
            return (*ptr1 - *ptr2);
        ptr1++;
        ptr2++;
        n--;
    }
    return (0);
}
 
// Test fonksiyonu
void test_memcmp(const char *s1, const char *s2, size_t n, const char *test_name, int is_null_test)
{
    int ft_result = ft_memcmp(s1, s2, n);
    int std_result = memcmp(s1, s2, n);
    printf("Test: %s\n", test_name);
    printf("ft_memcmp sonucu: %d\n", ft_result);
    printf("memcmp sonucu: %d\n", std_result);
    if (ft_result == std_result)
    {
        if (is_null_test)
            printf("Durum: GEÇTİ (Null karakter karşılaştırması)\n\n");
        else
            printf("Durum: GEÇTİ\n\n");
    }
    else
        printf("Durum: BAŞARISIZ\n\n");
}

int main(void)
{
    // Test senaryoları
    test_memcmp("Merhaba", "Merhaba", 7, "Eşit string'ler", 0);
    test_memcmp("Merhaba", "Merhaya", 7, "Farklı string'ler", 0);
    test_memcmp("Mer\0aba", "Mer\0aya", 7, "Null karakter karşılaştırması", 1);
    test_memcmp("Merhaba", "Merhaba", 0, "Sıfır bayt", 0);
    test_memcmp("Merhaba", "Merhaba", 9, "size +1", 0);

    printf("Testler Tamamlandı!\n");
    return 0;
}