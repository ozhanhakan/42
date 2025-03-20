/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testC09.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:49:59 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/20 22:50:37 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// Kütüphane fonksiyonlarının prototipleri
void	ft_putchar(char c);
void	ft_swap(int *a, int *b);
void	ft_putstr(char *str);
int	ft_strlen(char *str);
int	ft_strcmp(char *s1, char *s2);

int main() {
	ft_putchar('A');
	ft_putchar('\n');

	int a = 5, b = 10;
	ft_swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);

	ft_putstr("Hello, World!\n");

	char *str = "Hello";
	printf("Length of '%s' is %d\n", str, ft_strlen(str));

	char *s1 = "Hello";
	char *s2 = "World";
	printf("Comparison result: %d\n", ft_strcmp(s1, s2));

	return 0;
	}