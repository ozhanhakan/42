/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:17:15 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/01 01:17:26 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

void	print_test_result(int success, const char *test_name)
{
	if (success)
		printf("[\033[32mOK\033[0m] %s\n", test_name);
	else
	{
		printf("[\033[31mFAIL\033[0m] %s\n", test_name);
		exit(EXIT_FAILURE);
	}
}

void	run_test(void (*test)(), const char *test_name)
{
	printf("Running %-25s", test_name);
	test();
	printf("\033[32m✓\033[0m\n");
}