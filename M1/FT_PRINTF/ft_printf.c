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
** VARIADIC FUNCTIONS BELLEKTE NASIL ÇALIŞIR:
** 
** STACK YAPISII (örnek: ft_printf("Test: %d %c", 42, 'A')):
** 
** Yüksek Adres                    STACK FRAME
** ┌─────────────────────┐        ┌─────────────────────┐
** │     'A' (int)       │ ◄────  │  va_arg(args, int)  │
** │      (0x41)         │        │  4. çağrı           │
** ├─────────────────────┤        ├─────────────────────┤
** │        42           │ ◄────  │  va_arg(args, int)  │
** │     (0x2A)          │        │  3. çağrı           │
** ├─────────────────────┤        ├─────────────────────┤
** │ "Test: %d %c" ptr   │ ◄────  │  format parameter   │
** │   (string addr)     │        │  2. parameter       │
** ├─────────────────────┤        ├─────────────────────┤
** │   Return Address    │        │  Geri dönüş adresi  │
** └─────────────────────┘        └─────────────────────┘
** Düşük Adres                     
** 
** va_list args; -> Stack'teki variadic argümanları gösteren pointer
** va_start(args, format); -> args'ı format'tan sonraki ilk argümana işaret ettirir
** va_arg(args, type); -> args'ın gösterdiği adresten veri alır, sonraki argümana kaydırır
** va_end(args); -> args pointer'ını temizler (güvenlik için)
**
** ADIM ADIM BELLEK İŞLEMLERİ:
** 1. va_start(args, format) -> args = &format + sizeof(format)
** 2. va_arg(args, int) -> *args'ı int olarak oku, args += sizeof(int)
** 3. va_arg(args, int) -> *args'ı int olarak oku, args += sizeof(int)
** 4. va_end(args) -> args = NULL (güvenlik)
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
	va_list	args;      // Argüman listesini tutacak değişken (aslında char* pointer)
	int		count;     // Yazdırılan toplam karakter sayısı

	// NULL format kontrolü - güvenlik için
	if (!format)
		return (-1);
	
	count = 0;
	
	/*
	** BELLEK ADIM 1: va_start(args, format)
	** 
	** Stack'te format parametresinden sonraki ilk argümanın adresini hesaplar:
	** args = (char*)&format + sizeof(format)
	** 
	** Örnek: ft_printf("Test: %d", 42)
	** Stack durumu:
	** [Return Addr][format ptr][42] <- Stack
	**                    ^      ^
	**                    |      args buraya işaret eder
	**                    format burası
	*/
	va_start(args, format);
	
	// Format string'i parse et ve yazdır
	count = ft_parse_format(format, args);
	
	/*
	** BELLEK ADIM 4: va_end(args)
	** 
	** args pointer'ını temizler, güvenlik için NULL yapar
	** args = NULL
	** 
	** Bu adım zorunludur çünkü:
	** 1. Bellek sızıntısını önler
	** 2. Pointer'ın yanlış kullanımını önler
	** 3. Debugging'i kolaylaştırır
	*/
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
int ft_parse_format(const char *format, va_list args)
{
	int count;  // Toplam yazdırılan karakter sayısı
	int i;      // Format string indeksi

	count = 0;
	i = 0;

	// Format string'in sonuna kadar döngü
	while (format[i])
	{
		// % karakteri değilse, normal karakter olarak yazdır
		int ret = 0;
		if (format[i] != '%')
		{
			ret = ft_putchar_fd(format[i], 1);  // STDOUT'a yazdır
			// Hata kontrolü: Eğer yazma işlemi başarısız olursa hemen çık
			if (ret == -1)
				return (-1);
			count += ret;
			i++;
		}
		// % karakteri ise, format specifier kontrolü yap
		else
		{
			i++;  // % karakterini atla

			// Format specifier'a göre uygun handler'ı çağır
			// va_arg(args, type): args listesinden sıradaki argümanı belirtilen tipte alır
			if (format[i] == 'c')
				/*
				** BELLEK ADIM 2: va_arg(args, int) - KARAKTER İÇİN
				** 
				** Stack'ten int boyutunda (4 byte) veri alır:
				** 1. current_value = *(int*)args  // args'ın gösterdiği adresten int oku
				** 2. args += sizeof(int)          // args'ı sonraki argümana kaydır
				** 
				** Örnek: ft_printf("%c", 'A')
				** Stack'te 'A' karakter olarak gönderilir ama int olarak saklanır (0x00000041)
				** 
				** BELLEK DÜZENİ (4 byte alignment):
				** ┌─────────────────────┐
				** │    0x00000041       │ <- 'A' karakteri int olarak (4 byte)
				** └─────────────────────┘
				**  ^
				**  args buraya işaret eder, veri alındıktan sonra +4 byte kaydırılır
				**
				** Type promotion: char -> int (C standardı gereği)
				** Handler fonksiyonu (ft_print_char), aldığı int değeri karakter olarak basar.
				** Hata kontrolü: Handler -1 döndürürse, hemen -1 ile çıkılır.
				*/
				ret = ft_print_char(va_arg(args, int));
			else if (format[i] == 's')
				/*
				** BELLEK ADIM 3: va_arg(args, char *) - STRING İÇİN
				** 
				** Stack'ten pointer boyutunda (8 byte/64-bit) veri alır:
				** 1. current_value = *(char**)args  // args'ın gösterdiği adresten char* oku
				** 2. args += sizeof(char*)          // args'ı sonraki argümana kaydır
				** 
				** Örnek: ft_printf("%s", "Hello")
				** Stack'te "Hello" string'inin adresi saklanır
				** 
				** BELLEK DÜZENİ:
				** ┌─────────────────────┐    ┌─────────────────────┐
				** │   0x7fff12345678    │ -> │ "Hello\0"           │
				** └─────────────────────┘    └─────────────────────┘
				**  ^                           ^
				**  args buraya işaret eder     String heap'te burada
				**
				** Handler NULL kontrolü yapar, NULL ise "(null)" basar.
				*/
				ret = ft_print_string(va_arg(args, char *));
			else if (format[i] == 'p')
				/*
				** %p formatı için pointer argümanı alınır.
				** va_arg(args, void *): args listesinden void * tipinde argüman alır.
				** Örnek: ft_printf("%p", &variable); -> variable'ın adresi void * olarak alınır.
				** Handler adresi hexadecimal format ile "0x..." şeklinde basar.
				*/
				ret = ft_print_pointer(va_arg(args, void *));
			else if (format[i] == 'd' || format[i] == 'i')
				/*
				** %d ve %i formatları için signed integer argümanı alınır.
				** va_arg(args, int): args listesinden int tipinde argüman alır.
				** Örnek: ft_printf("%d", -42); -> -42 değeri int olarak alınır.
				** Handler negatif/pozitif kontrolü yapar, işareti ve sayıyı basar.
				*/
				ret = ft_print_decimal(va_arg(args, int));
			else if (format[i] == 'u')
				/*
				** %u formatı için unsigned integer argümanı alınır.
				** va_arg(args, unsigned int): args listesinden unsigned int tipinde alır.
				** Örnek: ft_printf("%u", 4294967295U); -> max unsigned int değeri alınır.
				** Handler sadece pozitif sayıları basar, negatif işaret olmaz.
				*/
				ret = ft_print_unsigned(va_arg(args, unsigned int));
			else if (format[i] == 'x')
				/*
				** %x formatı için hexadecimal (küçük harf) argümanı alınır.
				** va_arg(args, unsigned int): args listesinden unsigned int tipinde alır.
				** Örnek: ft_printf("%x", 255); -> ff olarak basar (küçük harf).
				** Handler sayıyı 16'lık tabana çevirir, a-f kullanır.
				*/
				ret = ft_print_hex_lower(va_arg(args, unsigned int));
			else if (format[i] == 'X')
				/*
				** %X formatı için hexadecimal (büyük harf) argümanı alınır.
				** va_arg(args, unsigned int): args listesinden unsigned int tipinde alır.
				** Örnek: ft_printf("%X", 255); -> FF olarak basar (büyük harf).
				** Handler sayıyı 16'lık tabana çevirir, A-F kullanır.
				*/
				ret = ft_print_hex_upper(va_arg(args, unsigned int));
			else if (format[i] == '%')
				/*
				** %% formatı için argüman alınmaz, sadece '%' karakteri basılır.
				** va_arg() kullanılmaz çünkü argüman listesinden bir şey alınmaz.
				** Örnek: ft_printf("%%"); -> % karakteri basılır.
				** Handler direkt '%' karakterini basar.
				*/
				ret = ft_print_percent();
			else
			{
				/*
				** BİLİNMEYEN FORMAT SPECIFIER İŞLEMİ
				** 
				** Örnek: ft_printf("%q", 42); -> %q tanımsız format
				** 
				** 1. Önce '%' karakteri basılır
				** 2. Sonra bilinmeyen karakter ('q') basılır
				** 3. Argüman listesinden hiçbir şey alınmaz (va_arg çağrılmaz)
				** 
				** Bu yaklaşım orijinal printf'in davranışını taklit eder.
				** Önemli: va_arg() çağrılmadığı için argüman listesi senkronizasyonu bozulabilir!
				** 
				** TEHLIKE: Eğer kullanıcı argüman vermiş ama format yanlışsa:
				** ft_printf("%q %d", 42, 100); 
				** -> %q için va_arg çağrılmaz, 42 argümanı atlanır
				** -> %d için va_arg(args, int) çağrılır, 100 yerine yanlış değer alınır
				** -> Stack corruption riski!
				*/
				// Bilinmeyen format specifier - orjinal printf davranışı
				ret = ft_putchar_fd('%', 1);
				if (ret == -1)
					return (-1);
				count += ret;
				ret = ft_putchar_fd(format[i], 1);
			}
			// Handler fonksiyonunda hata olursa hemen çık
			if (ret == -1)
				return (-1);
			count += ret;
			i++;
		}
	}
	return (count);
}
