/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:49:59 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/20 23:50:27 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int main(void) {
	// ft_putchar test
	ft_putchar('A');
	ft_putchar('\n');

	// ft_swap test
	int a = 5, b = 10;
	ft_swap(&a, &b);
	ft_putstr("a = ");
	ft_putchar(a + '0');  // int'i char'a dönüştür
	ft_putstr(", b = ");
	ft_putchar(b + '0');  // int'i char'a dönüştür
	ft_putchar('\n');

	// ft_putstr test
	ft_putstr("Hello, World!\n");

	// ft_strlen test
	char *str = "Hello";
	ft_putstr("Length of '");
	ft_putstr(str);
	ft_putstr("' is ");
	ft_putchar(ft_strlen(str) + '0');  // int'i char'a dönüştür
	ft_putchar('\n');

	// ft_strcmp test
	char *s1 = "Hello";
	char *s2 = "World";
	ft_putstr("Comparison result: ");
	ft_putchar(ft_strcmp(s1, s2) + '0');  // int'i char'a dönüştür
	ft_putchar('\n');

    return 0;
}