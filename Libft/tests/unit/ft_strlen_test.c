/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:49:04 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/01 01:17:49 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/libft.h"
#include "test_utils.h"
#include <string.h>

static void	test_normal_string(void)
{
	print_test_result(ft_strlen("hello") == 5, "normal_string");
}

static void	test_empty_string(void)
{
	print_test_result(ft_strlen("") == 0, "empty_string");
}

static void	test_null_pointer(void)
{
	print_test_result(ft_strlen(NULL) == 0, "null_pointer");
}

static void	test_long_string(void)
{
	char	long_str[10000];
	memset(long_str, 'a', 9999);
	long_str[9999] = '\0';
	print_test_result(ft_strlen(long_str) == 9999, "long_string");
}

static void	test_special_chars(void)
{
	char	special_str[] = {'\n', '\t', 0};
	print_test_result(ft_strlen(special_str) == 2, "special_chars");
}

int	main(void)
{
	printf("=== Testing ft_strlen ===\n");
	run_test(test_normal_string, "normal_string");
	run_test(test_empty_string, "empty_string");
	run_test(test_null_pointer, "null_pointer");
	run_test(test_long_string, "long_string");
	run_test(test_special_chars, "special_chars");
	printf("\033[32mAll tests passed!\033[0m\n");
	return (EXIT_SUCCESS);
}