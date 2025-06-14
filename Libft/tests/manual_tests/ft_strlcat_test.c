#include <stdio.h>
#include <string.h>
#include "../../src/libft.h"


size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	i = 0;
	while (src && i < size - 1 - dst_len)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

int main(void)
{
	// Test 1
	char *str = "the cake is a lie !\0I'm hidden lol\r\n";
	char buff1[0xF00] = "there is no stars in the sky";
	char buff2[0xF00] = "there is no stars in the sky";
	size_t max = strlen(str) + 4;
	size_t r1 = ft_strlcat(buff1, str, max);
	size_t r2 = ft_strlcat(buff2, str, max);
	printf("Test 1: max = %zu\n", max);
	printf("strlcat dönüş: %zu\n", r1);
	printf("ft_strlcat dönüş: %zu\n", r2);
	printf("buff2: %s\n", buff2);
	printf("Durum: %s\n\n", r1 == r2 ? "GEÇTİ" : "BAŞARISIZ");

	// Test 2
	char s1[4] = "";
	char s2[4] = "";
	r1 = ft_strlcat(s1, "thx to ntoniolo for this test !", 4);
	r2 = ft_strlcat(s2, "thx to ntoniolo for this test !", 4);
	printf("Test 2:\n");
	printf("strlcat dönüş: %zu\n", r1);
	printf("ft_strlcat dönüş: %zu\n", r2);
	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
	printf("Durum: %s\n\n", r1 == r2 ? "GEÇTİ" : "BAŞARISIZ");

	printf("Testler Tamamlandı!\n");
	return 0;
}