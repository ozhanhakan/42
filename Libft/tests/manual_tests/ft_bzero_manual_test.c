#include <stdio.h>
#include <string.h>     // orijinal bzero için
#include <unistd.h>     // write() için
#include <stdlib.h>     // malloc(), free() için
#include <stddef.h>     // size_t için
#include "../../src/libft.h"

/* // Kendi bzero fonksiyonumuz
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
} */


// Belleği hex formatında yazdırmak için yardımcı fonksiyon
void	print_bytes(const void *s, size_t n)
{
	const unsigned char *bytes = (const unsigned char *)s;
	for (size_t i = 0; i < n; i++)
	{
		printf("%d ", bytes[i]);
	}
	printf("\n");
}

int	main(void)
{
	size_t	len = 10;

	// Bellek ayır ve farklı değerlerle doldur
	char	*original = malloc(len);
	char	*custom = malloc(len);

	if (!original || !custom)
		return (1);

	// Örnek verilerle doldur
	for (size_t i = 0; i < len; i++)
	{
		original[i] = i + 1;
		custom[i] = i + 1;
	}

	// Orijinal bzero
	bzero(original, len-5);

	// Kendi bzero
	ft_bzero(custom, len-5);

	// Sonuçları yazdır
	printf("Original bzero:\n");
	print_bytes(original, len);

	printf("Custom ft_bzero:\n");
	print_bytes(custom, len);

	// Karşılaştırma
	if (memcmp(original, custom, len) == 0)
		printf("✅ Test geçti: ft_bzero doğru çalışıyor.\n");
	else
		printf("❌ Test başarısız: ft_bzero çıktısı farklı.\n");

	free(original);
	free(custom);
	return (0);
}
