#include <stdio.h>
#include <string.h> // strchr fonksiyonu için
#include "../../src/libft.h"

// Kendi ft_strchr fonksiyonun (kendi kodunla değiştir)
/* char *ft_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
} */

int main(void)
{
    const char *str = "hello";
    int c = 'l'; // Test edilecek karakteri buradan değiştir
    char *ft_result;
    char *std_result;

    ft_result = ft_strchr(str, c);
    std_result = strchr(str, c);

    printf("Test: '%c' in \"%s\"\n", c, str);
    printf("ft_strchr: %s\n", ft_result ? ft_result : "NULL");
    printf("strchr: %s\n", std_result ? std_result : "NULL");
    printf("Durum: %s\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");

    return 0;
}