/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:05:41 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 17:22:56 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	ft_print_char(int c)
{
	return (ft_putchar_fd((char)c, 1));
}

int	ft_print_string(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	return (ft_putstr_fd(str, 1));
}

int	ft_print_pointer(void *ptr)
{
	int		count;
	char	*hex_str;

	count = 0;
	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	count += ft_putstr_fd("0x", 1);	
	hex_str = ft_itoa_base((unsigned long)ptr, "0123456789abcdef");
	if (!hex_str)
		return (-1);
	count += ft_putstr_fd(hex_str, 1);
	free(hex_str);
	return (count);
}

int	ft_print_decimal(int n)
{
	char	*str;
	int		count;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}

int	ft_print_unsigned(unsigned int n)
{
	char	*str;
	int		count;

	str = ft_utoa(n);
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}
