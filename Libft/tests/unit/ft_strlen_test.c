/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:49:04 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/01 00:59:47 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

// 1. Temel Fonksiyonel Testler
void test_normal_string(void)
{
	TEST_ASSERT(ft_strlen("hello") == 5);
}

void test_empty_string(void)
{
	TEST_ASSERT(ft_strlen("") == 0);
}

// 2. Edge Case Testleri
void test_null_pointer(void) {
	printf("Testing NULL pointer... ");
	fflush(stdout);  // Çıktıyı hemen göster
	
	if (ft_strlen(NULL) == 0)
		printf(GREEN "✓\n" RESET);
	else {
		printf(RED "✗\n" RESET);
		exit(1);
	}
}

// 3. Uzun String Testi
void test_long_string(void)
{
	char long_str[10000];
	memset(long_str, 'a', 9999);
	long_str[9999] = '\0';
	TEST_ASSERT(ft_strlen(long_str) == 9999);
}

// 4. Özel Karakterler
void test_special_chars(void)
{
	TEST_ASSERT(ft_strlen("\n\t\0abc") == 2); // \0'a kadar sayar
}

int main(void)
{
	RUN_TEST(test_normal_string);
	RUN_TEST(test_empty_string);
	RUN_TEST(test_null_pointer);
	RUN_TEST(test_long_string);
	RUN_TEST(test_special_chars);
	printf(GREEN "✓ ft_strlen passed all tests!\n" RESET);
	return (0);
}
