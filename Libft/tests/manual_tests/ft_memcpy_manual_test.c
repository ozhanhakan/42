#include <stdio.h>
	#include <stdint.h>
	#include <string.h>
#include "libft.h"

void print_buffers(const char *label, const char *buf) {

	printf("%s: \"%s\"\n", label, buf);
}

int main() {

	char original1[] = "1234567890";
	char original2[] = "1234567890";
	char original3[] = "1234567890";

	printf("Before overlapping copy:\n");
	print_buffers("Original", original1);

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
