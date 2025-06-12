#include <stdio.h>
#include <string.h>

// ft_memchr fonksiyonunuzu buraya ekleyin (örnek olarak, sizin yazdığınızı varsayıyorum)
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	while (n--)
	{
		if (*ptr == (unsigned char)c)
			return (void *)ptr;
		ptr++;
	}
	return (NULL);
}


// Test sonuçlarını karşılaştırma ve yazdırma için yardımcı fonksiyon
void compare_results(void *ft_result, void *std_result, const char *test_name, int test_num, int c)
{
    printf("Test %d: %s\n", test_num, test_name);
    if (ft_result == std_result)
    {
        if (ft_result)
        {
            if (c == '\0')
                printf("ft_memchr sonucu: Doğru (adres: %p, Null karakter bulundu)\n", ft_result);
            else
                printf("ft_memchr sonucu: Doğru (adres: %p, karakter: %c)\n", ft_result, *(char *)ft_result);
        }
        else
            printf("ft_memchr sonucu: Doğru (NULL döndü)\n");
        if (std_result)
        {
            if (c == '\0')
                printf("memchr sonucu: Doğru (adres: %p, Null karakter bulundu)\n", std_result);
            else
                printf("memchr sonucu: Doğru (adres: %p, karakter: %c)\n", std_result, *(char *)std_result);
        }
        else
            printf("memchr sonucu: Doğru (NULL döndü)\n");
        printf("Durum: GEÇTİ\n\n");
    }
    else
    {
        printf("ft_memchr sonucu: Yanlış (dönen: %p)\n", ft_result);
        printf("memchr sonucu: Doğru (dönen: %p)\n", std_result);
        printf("Durum: BAŞARISIZ\n\n");
    }
}

// Test 1: Normal karakter arama
void test_normal_char(int *test_num)
{
    const char *str = "Merhaba";
    int c = 'r';
    size_t n = 7;
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Normal karakter arama ('r' in Merhaba)", *test_num, c);
    (*test_num)++;
}

// Test 2: Karakter bulunmaması
void test_char_not_found(int *test_num)
{
    const char *str = "Merhaba";
    int c = 'z';
    size_t n = 7;
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Karakter bulunmaması ('z' in Merhaba)", *test_num, c);
    (*test_num)++;
}

// Test 3: Null karakter arama
void test_null_char(int *test_num)
{
    const char *str = "Merhaba";
    int c = '\0';
    size_t n = 8; // Null karakter dahil
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Null karakter arama", *test_num, c);
    (*test_num)++;
}

// Test 4: Sıfır bayt arama
void test_zero_bytes(int *test_num)
{
    const char *str = "Merhaba";
    int c = 'r';
    size_t n = 0;
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Sıfır bayt arama (n=0)", *test_num, c);
    (*test_num)++;
}

// Test 5: Sınır durumu (son bayt)
void test_boundary(int *test_num)
{
    const char *str = "Merhaba";
    int c = 'a';
    size_t n = 7;
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Sınır durumu ('a' son baytta)", *test_num, c);
    (*test_num)++;
}

// Test 6: Boş string
void test_empty_string(int *test_num)
{
    const char *str = "";
    int c = 'a';
    size_t n = 1;
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Boş string", *test_num, c);
    (*test_num)++;
}

// Test 7: Non-ASCII karakter
void test_non_ascii(int *test_num)
{
    unsigned char str[] = {0xFF, 0xAA, 0xBB, 0x00};
    int c = 0xAA;
    size_t n = 4;
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    compare_results(ft_result, std_result, "Non-ASCII karakter (0xAA)", *test_num, c);
    (*test_num)++;
}

int main(void)
{
    int test_num = 1;
    printf("ft_memchr Testleri Başlıyor...\n\n");

    test_normal_char(&test_num);
    test_char_not_found(&test_num);
    test_null_char(&test_num);
    test_zero_bytes(&test_num);
    test_boundary(&test_num);
    test_empty_string(&test_num);
    test_non_ascii(&test_num);

    printf("Testler Tamamlandı!\n");
    return 0;
}