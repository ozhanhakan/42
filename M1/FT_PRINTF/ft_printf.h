/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:00:00 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/13 17:00:00 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>  // va_list, va_start, va_arg, va_end için gerekli
# include <unistd.h>  // write fonksiyonu için
# include <stdlib.h>  // malloc, free için
# include <stddef.h>  // size_t için

/*
** VARIADIC FUNCTIONS (Değişken Sayıda Argümanlı Fonksiyonlar):
** - printf("format", arg1, arg2, ...) gibi değişken sayıda parametre alan fonksiyonlar
** - stdarg.h kütüphanesi ile implement edilir
** - va_list: argüman listesini tutan veri tipi
** - va_start(): argüman listesini başlatır
** - va_arg(): sıradaki argümanı alır ve tipi belirtir
** - va_end(): argüman listesini temizler
*/

/*
** FORMAT SPECIFIERS (Biçim Belirteçleri):
** %c - char: tek karakter yazdırır
** %s - string: karakter dizisi yazdırır  
** %p - pointer: void* pointer'ı hexadecimal olarak yazdırır
** %d - decimal: signed integer'ı decimal olarak yazdırır
** %i - integer: %d ile aynı, signed integer decimal
** %u - unsigned: unsigned integer'ı decimal olarak yazdırır
** %x - hexadecimal: sayıyı küçük harfli hex olarak yazdırır (0-9, a-f)
** %X - Hexadecimal: sayıyı büyük harfli hex olarak yazdırır (0-9, A-F)
** %% - percent: % karakterini yazdırır
*/

// Ana printf fonksiyonu - printf()'in 42 versiyonu
int		ft_printf(const char *format, ...);

// Format string'i parse eder ve uygun handler'ı çağırır
int		ft_parse_format(const char *format, va_list args);

// Her format specifier için ayrı handler fonksiyonları
int		ft_print_char(int c);           // %c için
int		ft_print_string(char *str);     // %s için  
int		ft_print_pointer(void *ptr);    // %p için
int		ft_print_decimal(int n);        // %d ve %i için
int		ft_print_unsigned(unsigned int n);  // %u için
int		ft_print_hex_lower(unsigned int n); // %x için
int		ft_print_hex_upper(unsigned int n); // %X için
int		ft_print_percent(void);         // %% için

// Yardımcı fonksiyonlar
int		ft_putchar_fd(char c, int fd);  // Karakter yazdırma
int		ft_putstr_fd(char *s, int fd);  // String yazdırma
size_t	ft_strlen(const char *s);       // String uzunluğu
char	*ft_itoa(int n);               // Integer to ASCII
char	*ft_utoa(unsigned int n);      // Unsigned integer to ASCII
char	*ft_itoa_base(unsigned long n, char *base); // Sayıyı belirtilen tabanda string'e çevirir

#endif
