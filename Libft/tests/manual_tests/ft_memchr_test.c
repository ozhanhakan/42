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

int main(void)
{
    const char *str = "Merhaba";
    int c = '\0';
    size_t n = 8; // Null karakter dahil
    void *ft_result = ft_memchr(str, c, n);
    void *std_result = memchr(str, c, n);

    printf("Null Karakter Arama Testi\n");
    if (ft_result == std_result)
    {
        if (ft_result)
            printf("ft_memchr: Doğru (adres: %p, Null karakter bulundu)\n", ft_result);
        else
            printf("ft_memchr: Doğru (NULL döndü)\n");
        if (std_result)
            printf("memchr: Doğru (adres: %p, Null karakter bulundu)\n", std_result);
        else
            printf("memchr: Doğru (NULL döndü)\n");
        printf("Durum: GEÇTİ\n");
    }
    else
    {
        printf("ft_memchr: Yanlış (dönen: %p)\n", ft_result);
        printf("memchr: Doğru (dönen: %p)\n", std_result);
        printf("Durum: BAŞARISIZ\n");
    }

    return 0;
}
