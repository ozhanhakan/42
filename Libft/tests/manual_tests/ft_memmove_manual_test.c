#include <stdio.h>
#include <string.h>
#include "../../src/libft.h"


void	test_memmove(void)
{
	char	test1[20] = "1234567890";
	char	test2[20] = "1234567890";
	char	*result;
	char	*expected;

	printf("=== ft_memmove Testleri ===\n");

	// Test 1: Normal kopyalama
	result = ft_memmove(test1, "abcdef", 4);
	expected = memmove(test2, "abcdef", 4);
	printf("Test 1: %s -> %s (%s)\n", "1234567890", result, 
		strcmp(result, expected) == 0 ? "PASS" : "FAIL");

	// Test 2: Bellek çakışması (sola kaydırma)
	memcpy(test1, "1234567890", 11);
	memcpy(test2, "1234567890", 11);
	result = ft_memmove(test1 + 2, test1, 5);
	expected = memmove(test2 + 2, test2, 5);
	printf("Test 2: %s (%s)\n", result, 
		strcmp(result, expected) == 0 ? "PASS" : "FAIL");

	// Test 3: Bellek çakışması (sağa kaydırma)
	memcpy(test1, "1234567890", 11);
	memcpy(test2, "1234567890", 11);
	result = ft_memmove(test1, test1 + 2, 5);
	expected = memmove(test2, test2 + 2, 5);
	printf("Test 3: %s (%s)\n", result, 
		strcmp(result, expected) == 0 ? "PASS" : "FAIL");

	// Test 4: NULL pointer kontrolü (Segfault testi elle yapılmalı)
	// printf("Test 4: NULL pointer testi (elle kontrol edilmeli)\n");
}

int	main(void)
{
	test_memmove();
	return (0);
}