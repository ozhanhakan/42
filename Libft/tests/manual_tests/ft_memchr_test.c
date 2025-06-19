#include <stdio.h>
#include <string.h>
#include "../../src/libft.h"

// ft_memchr fonksiyonunuzu buraya ekleyin (örnek olarak, sizin yazdığınızı varsayıyorum)
/* void	*ft_memchr(const void *s, int c, size_t n)
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
} */

void test_memchr(const char *str, int c, size_t n)
{
    printf("\nTest: \"%s\" içinde '%c' (n = %zu)\n", str, (char)c, n);
    
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);
    
    printf("ft_memchr: ");
    if (ft_result)
        printf("Bulundu (%p) -> '%c'\n", ft_result, *(char *)ft_result);
    else
        printf("NULL\n");
    
    printf("memchr:    ");
    if (std_result)
        printf("Bulundu (%p) -> '%c'\n", std_result, *(char *)std_result);
    else
        printf("NULL\n");
    
    printf("Sonuç: %s\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");
}

int main(void)
{
    // Farklı test senaryoları
    test_memchr("Merhaba", 'a', 7);
    test_memchr("Merhaba", 'z', 7);
    test_memchr("Merhaba", 'M', 7);
    test_memchr("Merhaba", '\0', 8);
    test_memchr("Test\0string", 's', 11);
    test_memchr("", 'a', 1);
    
    return 0;
}
