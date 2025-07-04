#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <stddef.h>

static size_t    ft_strlen(const char *s)
{
	size_t    len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

size_t    ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t    len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (*src && --size)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (len);
}


#include <stdio.h>
int main(void)
{
	char dst[10];
	char *src = "Merhaba";
	size_t len = ft_strlcpy(dst, src, 5);
	printf("dst: %s, len: %zu\n", dst, len); // dst: Merh, len: 7
	return 0;
}