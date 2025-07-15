/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:05:41 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 15:25:02 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ft_print_char - %c format specifier handler
** @c: yazdırılacak karakter (int olarak alınır, char'a cast edilir)
**
** Return: yazdırılan karakter sayısı (1 veya hata durumunda -1)
**
** NOT: va_arg() ile char alırken int kullanılır çünkü C'de char otomatik
** olarak int'e promote edilir (argument promotion kuralları)
*/
int	ft_print_char(int c)
{
	return (ft_putchar_fd((char)c, 1));
}

/*
** ft_print_string - %s format specifier handler  
** @str: yazdırılacak string
**
** Return: yazdırılan karakter sayısı
**
** Özel Durumlar:
** - NULL pointer gelirse "(null)" yazdırır (printf davranışı)
** - Boş string ise 0 döner
*/
int	ft_print_string(char *str)
{
	// NULL kontrolü - printf()'in davranışını taklit et
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	return (ft_putstr_fd(str, 1));
}

/*
** ft_print_pointer - %p format specifier handler
** @ptr: yazdırılacak pointer
**
** Return: yazdırılan karakter sayısı
**
** Pointer Format:
** - Önce "0x" prefix'i yazdırılır
** - Sonra adres hexadecimal olarak yazdırılır
** - NULL pointer için "(nil)" yazdırılır (sistem bağımlı)
*/
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

/*
** ft_print_decimal - %d ve %i format specifier handler
** @n: yazdırılacak signed integer
**
** Return: yazdırılan karakter sayısı
**
** Decimal Format:
** - Negatif sayılar için '-' işareti
** - Pozitif/sıfır sayılar işaretsiz
*/
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

/*
** ft_print_unsigned - %u format specifier handler
** @n: yazdırılacak unsigned integer
**
** Return: yazdırılan karakter sayısı
**
** Unsigned Format:
** - Her zaman pozitif (işaretsiz)
** - 0'dan 4294967295'e kadar (32-bit sistemde)
*/
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

/*
** ft_print_hex_lower - %x format specifier handler
** @n: hexadecimal olarak yazdırılacak unsigned integer
**
** Return: yazdırılan karakter sayısı
**
** Hex Lower Format:
** - 0-9, a-f karakterleri kullanılır
** - Küçük harf (lowercase)
*/
int	ft_print_hex_lower(unsigned int n)
{
	char	*str;
	int		count;

	str = ft_itoa_base(n, "0123456789abcdef");
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}

/*
** ft_print_hex_upper - %X format specifier handler  
** @n: hexadecimal olarak yazdırılacak unsigned integer
**
** Return: yazdırılan karakter sayısı
**
** Hex Upper Format:
** - 0-9, A-F karakterleri kullanılır
** - Büyük harf (uppercase)
*/
int	ft_print_hex_upper(unsigned int n)
{
	char	*str;
	int		count;

	str = ft_itoa_base(n, "0123456789ABCDEF");
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}

/*
** ft_print_percent - %% format specifier handler
**
** Return: yazdırılan karakter sayısı (1)
**
** Percent Format:
** - Sadece '%' karakterini yazdırır
** - Escape sequence olarak kullanılır
*/
int	ft_print_percent(void)
{
	return (ft_putchar_fd('%', 1));
}
