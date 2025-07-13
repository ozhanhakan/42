/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:00:00 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/13 17:00:00 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** VARIADIC FUNCTIONS NASIL ÇALIŞIR:
** 
** 1. va_list args; -> Argüman listesini tutacak değişken tanımla
** 2. va_start(args, format); -> args'ı format parametresinden sonra başlat
** 3. va_arg(args, type); -> Sıradaki argümanı belirtilen tipte al
** 4. va_end(args); -> Argüman listesini temizle
**
** Örnek:
** ft_printf("Number: %d, Char: %c", 42, 'A');
** format = "Number: %d, Char: %c"
** args listesi: [42, 'A']
*/

/*
** ft_printf - printf fonksiyonunun 42 implementasyonu
** @format: yazdırılacak format string'i (örn: "Hello %s\n")
** @...: değişken sayıda argüman (variadic arguments)
** 
** Return: yazdırılan karakter sayısı, hata durumunda -1
**
** Çalışma Mantığı:
** 1. va_list ile argümanları al
** 2. Format string'i karakter karakter parse et
** 3. % gördüğünde format specifier'ı kontrol et
** 4. Uygun handler fonksiyonunu çağır
** 5. Yazdırılan karakter sayısını say ve döndür
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;      // Argüman listesini tutacak değişken
	int		count;     // Yazdırılan toplam karakter sayısı

	// NULL format kontrolü - güvenlik için
	if (!format)
		return (-1);
	
	count = 0;
	
	// Variadic arguments'ları başlat
	// va_start(args, format): args'ı format'tan sonraki parametrelerle başlatır
	va_start(args, format);
	
	// Format string'i parse et ve yazdır
	count = ft_parse_format(format, args);
	
	// Argüman listesini temizle - bellek sızıntısını önlemek için zorunlu
	va_end(args);
	
	return (count);
}

/*
** ft_parse_format - Format string'i parse eder ve uygun handler'ları çağırır
** @format: parse edilecek format string'i
** @args: variadic arguments listesi
**
** Return: yazdırılan toplam karakter sayısı
**
** Çalışma Mantığı:
** 1. Format string'i karakter karakter dolaş
** 2. Normal karakter ise direkt yazdır
** 3. % karakteri görürse, sonraki karaktere bak
** 4. Format specifier'a göre uygun handler'ı çağır
** 5. va_arg() ile argümanı uygun tipte al
*/
int	ft_parse_format(const char *format, va_list args)
{
	int	count;  // Toplam yazdırılan karakter sayısı
	int	i;      // Format string indeksi

	count = 0;
	i = 0;
	
	// Format string'in sonuna kadar döngü
	while (format[i])
	{
		// % karakteri değilse, normal karakter olarak yazdır
		if (format[i] != '%')
		{
			count += ft_putchar_fd(format[i], 1);  // STDOUT'a yazdır
			i++;
		}
		// % karakteri ise, format specifier kontrolü yap
		else
		{
			i++;  // % karakterini atla
			
			// Format specifier'a göre uygun handler'ı çağır
			if (format[i] == 'c')
				count += ft_print_char(va_arg(args, int));
			else if (format[i] == 's')
				count += ft_print_string(va_arg(args, char *));
			else if (format[i] == 'p')
				count += ft_print_pointer(va_arg(args, void *));
			else if (format[i] == 'd' || format[i] == 'i')
				count += ft_print_decimal(va_arg(args, int));
			else if (format[i] == 'u')
				count += ft_print_unsigned(va_arg(args, unsigned int));
			else if (format[i] == 'x')
				count += ft_print_hex_lower(va_arg(args, unsigned int));
			else if (format[i] == 'X')
				count += ft_print_hex_upper(va_arg(args, unsigned int));
			else if (format[i] == '%')
				count += ft_print_percent();
			else
			{
				// Bilinmeyen format specifier - orjinal printf davranışı
				count += ft_putchar_fd('%', 1);
				count += ft_putchar_fd(format[i], 1);
			}
			i++;
		}
	}
	return (count);
}
