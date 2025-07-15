/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:07:45 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 15:24:36 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Static function prototypes (internal utility functions)
*/
static int	ft_count_digits(long long n);
static int	ft_count_digits_unsigned(unsigned int n);
static int	ft_count_digits_base(unsigned long n, int base);
/**
 * TODO: silinecek eğer kullanılmıyorsa
 * ft_free - Dinamik olarak ayrılan belleği serbest bırakır
 * @ptr: Serbest bırakılacak pointer'ın adresi
 * Return: NULL yapar
 */
void	*ft_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
/*
** ft_putchar_fd - Tek bir karakteri belirtilen file descriptor'a yazar
** @c: yazdırılacak karakter
** @fd: file descriptor (1 = stdout, 2 = stderr)
**
** Return: başarıyla yazılan karakter sayısı (1) veya hata durumunda -1
**
** NOT: write() system call'u kullanır, buffer'lamaz
*/
int	ft_putchar_fd(char c, int fd)
{
	// write() system call'u: fd'ye 1 byte yaz
	// Return: yazılan byte sayısı (1) veya hata (-1)
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (1);
}

/*
** ft_putstr_fd - String'i belirtilen file descriptor'a yazar
** @s: yazdırılacak string
** @fd: file descriptor
**
** Return: yazılan karakter sayısı veya hata durumunda -1
**
** NULL string kontrolü: NULL gelirse hata döner
*/
int	ft_putstr_fd(char *s, int fd)
{
	int	len;
	int	i;

	if (!s)
		return (-1);
	
	len = 0;
	i = 0;
	
	// Her karakteri tek tek yaz ve sayacı artır
	while (s[i])
	{
		if (ft_putchar_fd(s[i], fd) == -1)
			return (-1);
		len++;
		i++;
	}
	
	return (len);
}

/*
** ft_strlen - String uzunluğunu hesaplar
** @s: uzunluğu hesaplanacak string
**
** Return: string uzunluğu (NULL terminator hariç)
**
** Standart kütüphane strlen() fonksiyonunun implementasyonu
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	
	len = 0;
	while (s[len])
		len++;
	
	return (len);
}

/*
** ft_itoa - Integer'ı string'e çevirir (decimal base)
** @n: çevrilecek integer
**
** Return: malloc ile ayrılan string veya NULL (hata durumunda)
**
** Memory Management:
** - Caller bu string'i free() etmek zorunda
** - Negatif sayılar için '-' işareti eklenir
**
** Algorithm:
** 1. Sayının digit sayısını hesapla
** 2. Negatif kontrolü yap  
** 3. String için bellek ayır
** 4. Sayıyı sondan başa doğru karakterlere çevir
*/
char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	long long		num;

	// Edge case: INT_MIN overflow'unu önlemek için long long kullan
	num = n;
	sign = (num < 0) ? 1 : 0;
	if (sign)
		num = -num;
	
	// Digit sayısını hesapla
	len = ft_count_digits(num) + sign;
	
	// Bellek ayır (+1 null terminator için)
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	
	str[len] = '\0';  // Null terminator
	
	// Sayıyı sondan başa doğru string'e çevir
	while (len > sign)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	
	// Negatif işareti ekle
	if (sign)
		str[0] = '-';
	
	return (str);
}

/*
** ft_utoa - Unsigned integer'ı string'e çevirir
** @n: çevrilecek unsigned integer
**
** Return: malloc ile ayrılan string veya NULL
**
** ft_itoa'nın unsigned versiyonu - işaret kontrolü yok
*/
char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		len;

	// Digit sayısını hesapla
	len = ft_count_digits_unsigned(n);
	
	// Bellek ayır
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	
	str[len] = '\0';
	
	// Sayıyı string'e çevir
	while (len > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	
	return (str);
}

/*
** ft_itoa_base - Sayıyı belirtilen base'de string'e çevirir
** @num: çevrilecek sayı (unsigned long - pointer'lar için)
** @base: kullanılacak base karakterleri (örn: "0123456789abcdef")
**
** Return: malloc ile ayrılan string veya NULL
**
** Supported Bases:
** - Binary: "01"
** - Octal: "01234567"  
** - Decimal: "0123456789"
** - Hex Lower: "0123456789abcdef"
** - Hex Upper: "0123456789ABCDEF"
*/
char	*ft_itoa_base(unsigned long num, char *base)
{
	char	*str;
	int		len;
	int		base_len;

	if (!base)
		return (NULL);
	
	base_len = (int)ft_strlen(base);
	if (base_len < 2)  // En az binary base olmalı
		return (NULL);
	
	// Digit sayısını hesapla
	len = ft_count_digits_base(num, base_len);
	
	// Bellek ayır
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	
	str[len] = '\0';
	
	// Sayıyı belirtilen base'de string'e çevir
	while (len > 0)
	{
		str[--len] = base[num % base_len];
		num /= base_len;
	}
	
	return (str);
}

/*
** ft_count_digits - Bir sayının decimal digit sayısını hesaplar
** @n: digit sayısı hesaplanacak sayı
**
** Return: digit sayısı (minimum 1)
*/
static int	ft_count_digits(long long n)
{
	int	count;

	if (n == 0)
		return (1);
	
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	
	return (count);
}

/*
** ft_count_digits_unsigned - Unsigned sayının digit sayısını hesaplar
*/
static int	ft_count_digits_unsigned(unsigned int n)
{
	int	count;

	if (n == 0)
		return (1);
	
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	
	return (count);
}

/*
** ft_count_digits_base - Belirtilen base'de digit sayısını hesaplar
*/
static int	ft_count_digits_base(unsigned long n, int base)
{
	int	count;

	if (n == 0)
		return (1);
	
	count = 0;
	while (n > 0)
	{
		n /= base;
		count++;
	}
	
	return (count);
}
