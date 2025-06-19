#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../../src/libft.h"

#include <stddef.h>

/* void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dst;
	s = (unsigned const char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
} */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	i = 0;
	if (!d && !s)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void print_buffers(const char *label, const char *buf) {

	printf("%s: \"%s\"\n", label, buf);
}

int main() {

	char original1[] = "1234567890";
	char original2[] = "1234567890";
	char original3[] = "1234567890";

	printf("Before overlapping copy:\n");
	print_buffers("Original", original1);
	//ft_memcpy(((void*)0), ((void*)0), 3);
	//memcpy(((void*)0), ((void*)0), 3);

	// Overlapping copy: dst = buf + 2, src = buf
	memcpy(original1 + 2, original1, 5);        // Undefined behavior
	ft_memcpy(original2 + 2, original2, 5);     // Undefined behavior
	memmove(original3 + 2, original3, 5);       // Well-defined

	printf("\nAfter memcpy with overlap:\n");
	print_buffers("memcpy   ", original1);
	print_buffers("ft_memcpy", original2);
	print_buffers("memmove  ", original3);

	return 0;
}
