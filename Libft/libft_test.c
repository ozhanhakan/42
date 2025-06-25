/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* libft_test.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: Gemini <gemini@google.com>                 +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2024/06/25 14:00:00 by Gemini            #+#    #+#             */
/* Updated: 2024/06/25 14:00:00 by Gemini           ###   ########.fr       */
/* */
/* ************************************************************************** */

// ===========================================================================
// BU DOSYAYI DERLEMEK İÇİN:
// gcc -Wall -Wextra -Werror -o test_libft libft_test.c
// ===========================================================================

#include <stdio.h>
#include <bsd/string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h> // open için
#include <stddef.h> // size_t için

// ===========================================================================
//                        FONKSİYON PROTOTİPLERİ (libft.h)
// ===========================================================================
// Kendi fonksiyonlarının birbirini çağırabilmesi için prototipleri buraya ekliyoruz.

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);


// ===========================================================================
//                          PART 1 - LIBC FONKSİYONLARI
// ===========================================================================

// --- ft_atoi.c ---

/**
 * @brief Boşluk karakteri olup olmadığını kontrol eder.
 * @param c Kontrol edilecek karakter.
 * @return Boşluk ise 1, değilse 0 döner.
 * @note Standart C kütüphanesindeki isspace fonksiyonu gibi çalışır.
 * (9-13 arası karakterler: \t, \n, \v, \f, \r) ve 32 (boşluk).
 */
static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/**
 * @brief Bir karakter dizisini (string) tamsayıya (integer) dönüştürür.
 * @param nptr Dönüştürülecek karakter dizisi.
 * @return Dönüştürülmüş tamsayı değeri.
 *
 * @details
 * 1. `ft_isspace` yardımcı fonksiyonu ile string başındaki boşlukları atlar.
 * 2. Opsiyonel olarak bir adet '+' veya '-' işareti olup olmadığını kontrol eder.
 * Eğer '-' varsa, sonuç negatif olacaktır.
 * 3. Sayısal karakterler ('0'-'9') bitene kadar okumaya devam eder.
 * 4. Her adımda, mevcut sonucu 10 ile çarpar ve yeni basamağı ekler.
 * 5. Son olarak, başta tespit edilen işarete göre sonucu döndürür.
 */
int	ft_atoi(const char *nptr)
{
	int		c;
	int		s;
	int		res;
	char	*str;

	str = (char *)nptr;
	c = 0;
	s = 1;
	res = 0;
	while (str[c] && (ft_isspace(str[c])))
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	while (str[c] && (str[c] >= '0' && str[c] <= '9'))
	{
		res = (str[c] - '0') + (res * 10);
		c++;
	}
	return (res * s);
}

// --- ft_bzero.c ---

/**
 * @brief Bir bellek bloğunun n byte'ını sıfırla ('\0') doldurur.
 * @param s Sıfırlanacak bellek bloğunun başlangıç adresi.
 * @param n Sıfırlanacak byte sayısı.
 *
 * @details
 * 1. Verilen `void *s` pointer'ını `unsigned char *ptr`'a dönüştürür.
 * Bu, byte byte işlem yapmayı sağlar.
 * 2. `n` sıfır olana kadar döngü devam eder.
 * 3. Her döngüde, `ptr`'nin gösterdiği adrese '\0' (sıfır) yazar ve
 * `ptr`'ı bir sonraki byte'a ilerletir.
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}

// --- ft_calloc.c ---

/**
 * @brief `nmemb` adet, her biri `size` byte olan bir bellek alanı ayırır
 * ve bu alanı sıfırlarla doldurur.
 * @param nmemb Ayrılacak eleman sayısı.
 * @param size Her bir elemanın boyutu (byte cinsinden).
 * @return Ayrılan bellek alanına bir pointer. Hata durumunda NULL döner.
 *
 * @details
 * 1. `malloc` kullanarak `nmemb * size` kadar toplam byte ayırır.
 * 2. `malloc` başarısız olursa (NULL dönerse), `ft_calloc` da NULL döner.
 * 3. Bellek başarıyla ayrılırsa, ayrılan alanın tamamını sıfırlamak için
 * `ft_bzero` fonksiyonunu çağırır.
 * 4. Ayrılan ve sıfırlanan bellek alanının başlangıç adresini döndürür.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	// Olası bir overflow'u kontrol etmek iyi bir pratiktir.
	// if (nmemb > 0 && size > 0 && nmemb > SIZE_MAX / size) return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}


// --- ft_isalnum.c ---

/**
 * @brief Verilen karakterin alfanümerik (harf veya rakam) olup olmadığını kontrol eder.
 * @param c Kontrol edilecek karakter (int olarak alınır).
 * @return Alfanümerik ise sıfırdan farklı bir değer, değilse 0 döner.
 */
int	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		|| (c >= '0' && c <= '9'));
}

// --- ft_isalpha.c ---

/**
 * @brief Verilen karakterin alfabetik (harf) olup olmadığını kontrol eder.
 * @param c Kontrol edilecek karakter.
 * @return Alfabetik ise sıfırdan farklı bir değer, değilse 0 döner.
 */
int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// --- ft_isascii.c ---

/**
 * @brief Verilen karakterin standart ASCII tablosunda (0-127) olup olmadığını kontrol eder.
 * @param c Kontrol edilecek karakter.
 * @return ASCII ise sıfırdan farklı bir değer, değilse 0 döner.
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// --- ft_isdigit.c ---

/**
 * @brief Verilen karakterin rakam ('0'-'9') olup olmadığını kontrol eder.
 * @param c Kontrol edilecek karakter.
 * @return Rakam ise sıfırdan farklı bir değer, değilse 0 döner.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// --- ft_isprint.c ---

/**
 * @brief Verilen karakterin yazdırılabilir bir karakter olup olmadığını kontrol eder.
 * @param c Kontrol edilecek karakter.
 * @return Yazdırılabilir ise (ASCII 32-126 arası), sıfırdan farklı bir değer,
 * değilse 0 döner.
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}


// --- ft_itoa.c ---
/**
 * @brief Bir sayının basamak sayısını hesaplar.
 * @param n Sayı.
 * @return Basamak sayısı (negatif işaret için ek bir basamak dahil).
 * @note Bu fonksiyon `ft_itoa` için yardımcıdır.
 */
static int	ft_int_len(int n)
{
	int			len;
	long long	nb;

	len = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

/**
 * @brief Tamsayıyı (integer) karakter dizisine (string) dönüştürür.
 * @param n Dönüştürülecek tamsayı.
 * @return Yeni oluşturulan string. Hata durumunda NULL döner.
 *
 * @details
 * 1. `ft_int_len` ile gereken bellek miktarını (basamak sayısı + null terminator) hesaplar.
 * 2. `malloc` ile bu boyutta bir bellek alanı ayırır.
 * 3. Özel durumları ele alır: `n = 0` ise stringe "0" yazar.
 * 4. Sayı negatifse, daha sonra eklemek üzere `long long nb` pozitif kopyasını oluşturur.
 * 5. Bir döngü içinde, sayının son basamağını alır (`nb % 10`), '0' ekleyerek karaktere çevirir
 * ve stringin sonundan başlayarak ilgili yere yazar.
 * 6. Sayı negatifse, stringin başına '-' işaretini ekler.
 * 7. Oluşturulan stringi döndürür.
 */
char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long long	nb;

	len = ft_int_len(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	nb = n;
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[--len] = '-';
	return (str);
}


// --- ft_memchr.c ---

/**
 * @brief Bellek bloğunda bir karakteri (byte) arar.
 * @param s Aranacak bellek bloğu.
 * @param c Aranacak karakter (byte değeri).
 * @param n Taranacak byte sayısı.
 * @return Karakterin ilk bulunduğu yerin pointer'ını veya bulunamazsa NULL döner.
 *
 * @details
 * 1. `void *s` pointer'ını `const unsigned char *ptr`'a dönüştürür.
 * 2. `n` byte boyunca döngüye girer.
 * 3. Her byte'ı aranan `c` karakteri ile karşılaştırır.
 * 4. Eşleşme bulunursa, o anki `ptr` adresini `void *` olarak döndürür.
 * 5. Döngü biter ve karakter bulunamazsa `NULL` döndürür.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	while (n--)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}


// --- ft_memcmp.c ---

/**
 * @brief İki bellek bloğunu `n` byte kadar karşılaştırır.
 * @param s1 Birinci bellek bloğu.
 * @param s2 İkinci bellek bloğu.
 * @param n Karşılaştırılacak byte sayısı.
 * @return Farklı ilk byte'lar arasındaki farkı (`s1[i] - s2[i]`) veya
 * `n` byte boyunca eşitse 0 döner.
 *
 * @details
 * 1. Pointer'ları `const unsigned char *` türüne çevirir.
 * 2. `n` sıfır ise hemen 0 döndürür.
 * 3. `n` byte boyunca döngüye girer.
 * 4. Her adımda, `ptr1` ve `ptr2`'nin gösterdiği byte'ları karşılaştırır.
 * 5. Farklı bir byte bulursa, aralarındaki farkı (unsigned char olarak) döndürür.
 * 6. Döngü biter ve fark bulunmazsa 0 döndürür.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	if (n == 0)
		return (0);
	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (n)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
		n--;
	}
	return (0);
}


// --- ft_memcpy.c ---

/**
 * @brief `src` bellek alanından `dest` bellek alanına `n` byte kopyalar.
 * @param dest Hedef bellek alanı.
 * @param src Kaynak bellek alanı.
 * @param n Kopyalanacak byte sayısı.
 * @return `dest` pointer'ını döndürür.
 * @warning Bellek alanları üst üste binerse (overlap) tanımsız davranışa yol açar.
 * Bu durumlar için `ft_memmove` kullanılmalıdır.
 *
 * @details
 * 1. Pointer'ları `unsigned char *` türüne çevirir.
 * 2. `dest` ve `src` NULL ise NULL döner (güvenlik kontrolü).
 * 3. `n` byte boyunca, `src`'den `dest`'e byte byte kopyalama yapar.
 * 4. Orijinal `dest` pointer'ını döndürür.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	if (!d && !s)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}


// --- ft_memmove.c ---

/**
 * @brief `src` bellek alanından `dest` bellek alanına `n` byte kopyalar.
 * Bu fonksiyon, bellek alanları üst üste bindiğinde (overlap) bile
 * güvenli bir şekilde çalışır.
 * @param dest Hedef bellek alanı.
 * @param src Kaynak bellek alanı.
 * @param n Kopyalanacak byte sayısı.
 * @return `dest` pointer'ını döndürür.
 *
 * @details
 * 1. Pointer'ları `unsigned char *` türüne çevirir.
 * 2. `dest` ve `src` NULL ise NULL döner.
 * 3. Eğer `dest` adresi `src`'den küçükse, kopyalamayı baştan sona doğru yapar.
 * Bu, olası bir overlap durumunda `src`'deki verinin üzerine yazılmadan önce
 * kopyalanmasını sağlar.
 * 4. Eğer `dest` adresi `src`'den büyükse, kopyalamayı sondan başa doğru yapar.
 * Bu da diğer overlap senaryosunda verinin bozulmasını engeller.
 * 5. Orijinal `dest` pointer'ını döndürür.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest && !src)
		return ((void *)dest);
	if (d == s)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n; // DİKKAT: Kodunuzda d += n - 1 idi. Sondaki elemana gitmek için
		s += n; // d += n ve s += n yapıp, sonra --d ve --s kullanmak daha güvenli olabilir.
				// VEYA d += n - 1; s += n - 1; ile başlayıp while(n--) *d-- = *s--; yapılabilir.
				// Orijinal kodunuz doğru çalışıyor, bu sadece bir alternatif.
		while (n--)
			*--d = *--s;
	}
	return ((void *)dest);
}

// --- ft_memset.c ---

/**
 * @brief Bir bellek bloğunun ilk `n` byte'ını belirtilen bir `c` değeriyle doldurur.
 * @param s Doldurulacak bellek bloğunun başlangıç adresi.
 * @param c Doldurulacak değer (int olarak alınır, unsigned char'a çevrilir).
 * @param n Doldurulacak byte sayısı.
 * @return `s` pointer'ını döndürür.
 *
 * @details
 * 1. `void *s` pointer'ını `unsigned char *ptr`'a dönüştürür.
 * 2. Bir `i` sayacı ile `n`'e kadar döner.
 * 3. Her adımda, `ptr[i]`'ye `c` değerini atar.
 * 4. Döngü bittikten sonra orijinal `s` pointer'ını döndürür.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// --- ft_putchar_fd.c ---

/**
 * @brief `c` karakterini belirtilen dosya tanıtıcısına (file descriptor) yazar.
 * @param c Yazılacak karakter.
 * @param fd Yazılacak dosya tanıtıcısı (örn: 1 for stdout).
 *
 * @details
 * `write` sistem çağrısını kullanarak, `c` karakterinin adresini ve 1 byte'lık
 * boyutunu vererek yazma işlemini gerçekleştirir.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// --- ft_putendl_fd.c ---

/**
 * @brief `s` stringini belirtilen dosya tanıtıcısına yazar ve sonuna bir
 * yeni satır karakteri ('\n') ekler.
 * @param s Yazılacak string.
 * @param fd Yazılacak dosya tanıtıcısı.
 *
 * @details
 * 1. `s` NULL ise hiçbir şey yapmaz.
 * 2. `ft_putstr_fd` kullanarak stringi yazar.
 * 3. `ft_putchar_fd` kullanarak yeni satır karakterini yazar.
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// --- ft_putnbr_fd.c ---

/**
 * @brief `n` tamsayısını belirtilen dosya tanıtıcısına yazar.
 * @param n Yazılacak tamsayı.
 * @param fd Yazılacak dosya tanıtıcısı.
 *
 * @details
 * 1. En küçük tamsayı (`-2147483648`) özel durumunu ele alır, çünkü `-n` işlemi
 * bu sayıda taşmaya (overflow) neden olur.
 * 2. Sayı negatifse, '-' işareti yazar ve sayıyı pozitife çevirir.
 * 3. Sayı 10'dan büyük veya eşitse, fonksiyon kendini rekürsif olarak çağırarak
 * bir önceki basamağı yazdırır.
 * 4. Son basamağı (`n % 10`) alıp '0' ekleyerek karaktere çevirir ve yazar.
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

// --- ft_putstr_fd.c ---

/**
 * @brief `s` stringini belirtilen dosya tanıtıcısına yazar.
 * @param s Yazılacak string.
 * @param fd Yazılacak dosya tanıtıcısı.
 *
 * @details
 * 1. `s` NULL ise hiçbir şey yapmaz.
 * 2. `ft_strlen` ile stringin uzunluğunu bulur.
 * 3. `write` sistem çağrısını kullanarak tüm stringi tek seferde yazar.
 */
void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}


// --- ft_split.c ---

/**
 * @brief Verilen string `s` içinde, ayırıcı `c` karakterine göre kaç kelime
 * olduğunu sayar.
 * @note `ft_split` için yardımcı fonksiyondur.
 */
static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	// Baştaki ayırıcıları atla
	while (s[i] && s[i] == c)
		i++;
	// String sonuna kadar git
	while (s[i])
	{
		words++;
		// Kelimenin sonuna git
		while (s[i] && s[i] != c)
			i++;
		// Ayırıcıların sonuna git
		while (s[i] && s[i] == c)
			i++;
	}
	return (words);
}

/**
 * @brief Hata durumunda, o ana kadar `ft_split` içinde ayrılmış tüm bellek
 * alanlarını serbest bırakır.
 * @note `ft_split` için yardımcı fonksiyondur.
 */
static void	ft_free_all(char **arr, size_t count)
{
	while (count--)
		free(arr[count]);
	free(arr);
}

/**
 * @brief Kelimeleri `ft_substr` kullanarak ayırır ve sonuç dizisine (`res`) doldurur.
 * @return Başarılı olursa 0, hata olursa 1 döner.
 * @note `ft_split` için yardımcı fonksiyondur.
 */
static int	ft_fill_words(char const *s, char c, char **res, size_t wc)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = -1;
	start = 0;
	while (++i < wc)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		res[i] = ft_substr(s, start, end - start);
		if (!res[i])
		{
			ft_free_all(res, i);
			return (1); // Hata
		}
		start = end;
	}
	res[i] = NULL; // Dizinin sonunu işaretle
	return (0); // Başarılı
}

/**
 * @brief `s` stringini, `c` karakterini ayırıcı olarak kullanarak böler ve
 * yeni bir string dizisi oluşturur.
 * @param s Bölünecek string.
 * @param c Ayırıcı karakter.
 * @return String dizisine bir pointer. Hata durumunda NULL döner. Dizi NULL ile sonlanır.
 *
 * @details
 * 1. `s` NULL ise NULL döner.
 * 2. `ft_count_words` ile kaç tane kelime (alt string) olacağını hesaplar.
 * 3. Bu kelime sayısı + 1 (NULL terminator için) boyutunda bir `char **` için bellek ayırır.
 * 4. `ft_fill_words` fonksiyonu ile ana döngüyü çalıştırır:
 * a. Ayırıcıları atlar.
 * b. Kelimenin başlangıcını ve sonunu bulur.
 * c. `ft_substr` ile kelimeyi kopyalayıp sonuç dizisine atar.
 * d. `ft_substr` başarısız olursa, o ana kadar ayrılan tüm belleği `ft_free_all` ile temizler.
 * 5. Sonuç dizisinin sonuna NULL pointer koyar ve diziyi döndürür.
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (ft_fill_words(s, c, result, word_count))
		return (NULL);
	return (result);
}


// --- ft_strchr.c ---

/**
 * @brief Bir string içinde bir karakterin ilk görüldüğü yeri bulur.
 * @param s Aranacak string.
 * @param c Aranacak karakter.
 * @return Karakterin bulunduğu yere bir pointer veya bulunamazsa NULL döner.
 * Eğer `c` null karakter ('\0') ise, stringin sonundaki null terminator'e
 * bir pointer döndürür.
 *
 * @details
 * 1. Stringin başından sonuna kadar döner.
 * 2. Her karakteri aranan `c` ile karşılaştırır.
 * 3. Eşleşme bulunursa, o anki adresi döndürür.
 * 4. Döngü bittiğinde (null terminator'e ulaşıldığında), eğer aranan `c` de
 * null terminator ise, o anki adresi döndürür.
 * 5. Aksi takdirde NULL döndürür.
 */
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == '\0')
		return (ptr);
	return (NULL);
}


// --- ft_strdup.c ---

/**
 * @brief Verilen `src` stringinin bir kopyasını oluşturur.
 * @param src Kopyalanacak string.
 * @return Yeni oluşturulan kopyalanmış string'e bir pointer.
 * Bellek ayırma hatasında NULL döner.
 *
 * @details
 * 1. `ft_strlen` ile kaynak stringin uzunluğunu bulur.
 * 2. `malloc` ile `uzunluk + 1` (null terminator için) byte yer ayırır.
 * 3. `malloc` başarısız olursa NULL döner.
 * 4. `ft_memcpy` ile kaynak stringin içeriğini yeni ayrılan belleğe kopyalar.
 * 5. Kopyalanan stringin sonuna null terminator ekler.
 * 6. Yeni stringin adresini döndürür.
 */
char	*ft_strdup(const char *src)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(src);
	copy = (char *)malloc(sizeof(char) * len + 1);
	if (copy == 0)
		return (NULL);
	ft_memcpy(copy, src, len);
	copy[len] = '\0';
	return (copy);
}


// --- ft_striteri.c ---

/**
 * @brief Bir stringin her karakterine, o karakterin indeksi ile birlikte
 * belirtilen bir fonksiyonu uygular. Karakterin kendisi değiştirilebilir.
 * @param s Üzerinde işlem yapılacak string.
 * @param f Her karaktere uygulanacak fonksiyon. Fonksiyon, karakterin
 * indeksini (`unsigned int`) ve karakterin adresini (`char*`) alır.
 *
 * @details
 * 1. `s` veya `f` NULL ise hiçbir şey yapmaz.
 * 2. Stringin başından sonuna kadar bir `i` sayacı ile döner.
 * 3. Her döngüde, `f(i, &s[i])` çağrısını yapar. `&s[i]` gönderildiği için,
 * `f` fonksiyonu orijinal stringdeki karakteri değiştirebilir.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}


// --- ft_strjoin.c ---

/**
 * @brief İki stringi (`s1` ve `s2`) birleştirerek yeni bir string oluşturur.
 * @param s1 İlk string (ön ek).
 * @param s2 İkinci string (son ek).
 * @return Yeni oluşturulan birleşik string. Hata durumunda NULL döner.
 *
 * @details
 * 1. `s1` veya `s2` NULL ise NULL döner.
 * 2. `ft_strlen` ile iki stringin de uzunluklarını hesaplar.
 * 3. `malloc` ile `len1 + len2 + 1` boyutunda yeni bir bellek alanı ayırır.
 * 4. `ft_memcpy` kullanarak önce `s1`'i yeni stringin başına kopyalar.
 * 5. Ardından, `s2`'yi `s1`'in bittiği yerden itibaren kopyalar. `len2 + 1`
 * kopyalanarak `s2`'nin null terminator'ü de kopyalanmış olur.
 * 6. Yeni oluşturulan stringi döndürür.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2 + 1);
	return (new_str);
}


// --- ft_strlcat.c ---

/**
 * @brief `src` stringini `dst` stringinin sonuna ekler (birleştirir).
 * Bu işlem, `dst` arabelleğinin toplam `size` boyutunu aşmayacak
 * şekilde güvenli bir şekilde yapılır.
 * @param dst Hedef string.
 * @param src Kaynak string.
 * @param size `dst` arabelleğinin toplam boyutu.
 * @return Birleştirme denenseydi oluşacak toplam string uzunluğunu
 * (`dst`'nin orijinal uzunluğu + `src`'nin uzunluğu) döndürür.
 *
 * @details
 * 1. `dst_len`'i, `size` sınırını aşmadan `dst`'nin mevcut uzunluğunu
 * bulmak için hesaplar.
 * 2. Eğer `dst_len` zaten `size`'a eşit veya büyükse, bu `dst`'nin dolu olduğu
 * veya `size`'ın geçersiz olduğu anlamına gelir. Bu durumda, `size + src_len`
 * döndürülür, ki bu da ne kadar tampona ihtiyaç duyulacağını gösterir.
 * 3. `src` stringini, `dst_len + i + 1 < size` koşulu sağlanana kadar `dst`'nin
 * sonuna kopyalar. `+1` null terminator için yer bırakır.
 * 4. Kopyalama bittikten sonra `dst`'nin sonuna null terminator ekler.
 * 5. `dst`'nin başlangıçtaki uzunluğu ile `src`'nin toplam uzunluğunu döndürür.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst); // Orijinal kodunuzdan farklı olarak ft_strlen kullanmak daha temiz.
	src_len = ft_strlen(src);
	if (size <= dst_len) // Eğer size, dst'nin mevcut uzunluğundan küçük veya eşitse
		return (size + src_len); // Sadece potansiyel uzunluğu dön.

	i = 0;
	while (src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}


// --- ft_strlcpy.c ---

/**
 * @brief `src` stringini `dst`'ye kopyalar. Bu işlem, `dst` arabelleğinin
 * toplam `size` boyutunu aşmayacak şekilde güvenli bir şekilde yapılır.
 * @param dst Hedef arabellek.
 * @param src Kaynak string.
 * @param size `dst` arabelleğinin toplam boyutu.
 * @return Kaynak string `src`'nin toplam uzunluğunu döndürür.
 *
 * @details
 * 1. Kaynak string `src`'nin uzunluğunu hesaplar. Bu, arabellek boyutundan
 * bağımsız olarak her zaman döndürülecek değerdir.
 * 2. Eğer `size` 0 ise, hiçbir şey kopyalanmaz.
 * 3. `src`'den `dst`'ye `size - 1` karakter kopyalanana veya `src` bitene
 * kadar kopyalama yapar.
 * 4. `dst`'nin sonuna her zaman bir null terminator ekler.
 * 5. Başlangıçta hesaplanan `src`'nin tam uzunluğunu döndürür.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t  i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);

	i = 0;
	while(src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';

	return (src_len);
}

// --- ft_strlen.c ---

/**
 * @brief Bir stringin null terminator ('\0') hariç uzunluğunu hesaplar.
 * @param s Uzunluğu hesaplanacak string.
 * @return Stringdeki karakter sayısı.
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

// --- ft_strmapi.c ---

/**
 * @brief `s` stringinin her bir karakterine `f` fonksiyonunu uygulayarak
 * yeni bir string oluşturur.
 * @param s Üzerinde işlem yapılacak string.
 * @param f Her karaktere uygulanacak fonksiyon. Bu fonksiyon, karakterin
 * indeksini (`unsigned int`) ve değerini (`char`) alır, yeni
 * bir karakter (`char`) döndürür.
 * @return `f` fonksiyonunun sonuçlarından oluşan yeni string. Hata durumunda NULL.
 *
 * @details
 * 1. `s` veya `f` NULL ise NULL döner.
 * 2. `s`'nin uzunluğu kadar yeni bir bellek alanı ayırır.
 * 3. `s` üzerinde dönerken, her `s[i]` karakteri için `f(i, s[i])` çağrısı yapar
 * ve dönen değeri yeni stringin `i`. indeksine atar.
 * 4. Yeni stringin sonuna null terminator ekler ve döndürür.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*new_str;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * s_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new_str[i] = f((unsigned int)i, s[i]);
		i++;
	}
	new_str[s_len] = '\0';
	return (new_str);
}

// --- ft_strncmp.c ---

/**
 * @brief İki stringi en fazla `n` karaktere kadar karşılaştırır.
 * @param s1 Birinci string.
 * @param s2 İkinci string.
 * @param n Karşılaştırılacak maksimum karakter sayısı.
 * @return Farklı ilk karakterler arasındaki farkı (`s1[i] - s2[i]`) veya
 * `n` karakter boyunca eşitse 0 döner.
 *
 * @details
 * 1. `n` sıfır ise hemen 0 döner.
 * 2. Bir `i` sayacı ile `n - 1`'e kadar veya stringlerden biri bitene veya
 * karakterler farklılaşana kadar döner.
 * 3. Döngüden çıktığında, `s1[i]` ve `s2[i]`'nin `unsigned char`'a
 * çevrilmiş hallerinin farkını döndürür. Bu, döngünün bittiği noktadaki
 * durumu yansıtır.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


// --- ft_strnstr.c ---

/**
 * @brief `big` stringi içinde, `little` stringinin ilk `len` byte'ta
 * bulunan ilk örneğini bulur.
 * @param big İçinde arama yapılacak string.
 * @param little Aranacak alt string.
 * @param len `big` stringinde aranacak maksimum byte sayısı.
 * @return `little` bulunursa, `big` içindeki başlangıç adresine bir pointer;
 * `little` boş ise `big`'e bir pointer; bulunamazsa NULL döner.
 *
 * @details
 * 1. `little` boş bir string ise, `big`'in başlangıcını döndürür.
 * 2. `big` stringi üzerinde `i` sayacı ile döner. Döngü, `big`'in sonuna
 * gelmeden veya `len` sınırına ulaşmadan önce, `little`'ın sığabileceği
 * son noktaya kadar devam eder (`i + little_len <= len`).
 * 3. Her `i` pozisyonu için, `little` stringinin `big` stringinin `i`'den
 * başlayan kısmıyla eşleşip eşleşmediğini kontrol etmek için iç içe bir
 * `j` döngüsü başlatır.
 * 4. Eğer iç döngü `little`'ın sonuna kadar tam bir eşleşme bulursa,
 * `big`'in `i`. karakterinin adresini döndürür.
 * 5. Eşleşme bulunmazsa, dış döngü devam eder.
 * 6. Dış döngü biter ve eşleşme bulunmazsa NULL döner.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	i = 0;
	if (little[0] == '\0') // veya !*little
		return ((char *)big);
	while (big[i] && i + little_len <= len)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
		{
			j++;
		}
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}


// --- ft_strrchr.c ---

/**
 * @brief Bir string içinde bir karakterin *son* görüldüğü yeri bulur.
 * @param s Aranacak string.
 * @param c Aranacak karakter.
 * @return Karakterin bulunduğu son yere bir pointer veya bulunamazsa NULL döner.
 * Eğer `c` null karakter ('\0') ise, stringin sonundaki null terminator'e
 * bir pointer döndürür.
 *
 * @details
 * 1. Stringin uzunluğunu bulur.
 * 2. Aranan `c` null karakter ise, `s + uzunluk` adresini döndürür.
 * 3. Stringin sonundan başına doğru bir döngü başlatır.
 * 4. Aranan karakteri bulduğu ilk anda (sondan gelirken ilk olan), o adresi
 * döndürür.
 * 5. Döngü biter ve karakter bulunamazsa NULL döndürür.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = ft_strlen(s);
	if ((char)c == '\0')
		return (ptr + i);
	while (i > 0) // i-- yerine i > 0 kullanmak s[0]'ı da kontrol eder
	{
		i--;
		if (ptr[i] == (char)c)
			return (ptr + i);
	}
	if (ptr[0] == (char)c) // Döngü bittikten sonra ilk karakteri de kontrol et.
		return (ptr);     // Veya döngü `while (i-- > 0)` şeklinde kurulabilir.
	return (NULL);
}


// --- ft_strtrim.c ---

/**
 * @brief Bir karakterin, verilen `set` stringi içindeki karakterlerden
 * biri olup olmadığını kontrol eder.
 * @note `ft_strtrim` için yardımcı fonksiyondur.
 */
static int	ft_is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief `s1` stringinin başından ve sonundan, `set` stringinde belirtilen
 * karakterleri temizler (kırpar).
 * @param s1 Kırpılacak string.
 * @param set Kırpılacak karakterleri içeren set.
 * @return Kırpılmış yeni string. Hata durumunda NULL döner.
 *
 * @details
 * 1. `s1` veya `set` NULL ise NULL döner.
 * 2. Bir `start` sayacı ile `s1`'in başından ilerleyerek `set`'te bulunan
 * karakterleri atlar.
 * 3. Bir `end` sayacı ile `s1`'in sonundan geriye gelerek `set`'te bulunan
 * karakterleri atlar.
 * 4. Eğer `start`, `end`'den büyük olursa, bu tüm stringin kırpıldığı anlamına gelir.
 * Bu durumda boş bir string döndürülür.
 * 5. `ft_substr` veya benzer bir mantıkla, `start` ve `end` arasındaki
 * kısım için yeni bir bellek alanı ayırır ve bu alt stringi oraya kopyalar.
 * 6. Yeni oluşturulan kırpılmış stringi döndürür.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_in_set(s1[end - 1], set))
		end--;
	// ft_substr kullanmak kodu kısaltır ve yeniden kullanımı artırır.
	trimmed_str = ft_substr(s1, start, end - start);
	return (trimmed_str);
}


// --- ft_substr.c ---

/**
 * @brief `s` stringinden bir alt string (substring) oluşturur.
 * @param s Kaynak string.
 * @param start Alt stringin başlangıç indeksi.
 * @param len Alt stringin maksimum uzunluğu.
 * @return Yeni oluşturulan alt string. Hata durumunda NULL döner.
 *
 * @details
 * 1. `s` NULL ise NULL döner.
 * 2. Eğer `start` indeksi `s`'nin uzunluğundan büyük veya eşitse, bu,
 * başlangıcın stringin dışında olduğu anlamına gelir. Bu durumda,
 * `malloc` ile 1 byte'lık yer ayarlanıp içine `\0` konarak boş bir
 * string döndürülür.
 * 3. Kopyalanacak gerçek uzunluk (`actual_len`) hesaplanır. Bu, ya istenen
 * `len`'dir ya da `s`'nin sonuna kadar olan kalan karakter sayısıdır
 * (hangisi daha küçükse).
 * 4. `malloc` ile `actual_len + 1` kadar yer ayırılır.
 * 5. `ft_strlcpy` (veya benzeri) kullanılarak `s`'nin `start`'tan başlayan
 * kısmı yeni belleğe kopyalanır.
 * 6. Yeni alt string döndürülür.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	actual_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		// Boş bir string döndürmek standart bir yaklaşımdır.
		return (ft_strdup(""));
	}
	if (len > (s_len - start))
		actual_len = s_len - start;
	else
		actual_len = len;
	sub = (char *)malloc(actual_len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, actual_len); // memcpy daha verimli olabilir
	sub[actual_len] = '\0';
	return (sub);
}


// --- ft_tolower.c ---

/**
 * @brief Büyük harfi küçük harfe çevirir.
 * @param c Çevrilecek karakter.
 * @return Eğer karakter büyük harf ise küçük harf karşılığı, değilse
 * karakterin kendisi döndürülür.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32); // 'a' - 'A' = 32
	return (c);
}


// --- ft_toupper.c ---

/**
 * @brief Küçük harfi büyük harfe çevirir.
 * @param c Çevrilecek karakter.
 * @return Eğer karakter küçük harf ise büyük harf karşılığı, değilse
 * karakterin kendisi döndürülür.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32); // 'a' - 'A' = 32
	return (c);
}



// ===========================================================================
//                              TEST FONKSİYONLARI
// ===========================================================================

// Testler için yardımcı fonksiyon
void print_result(int success)
{
	if (success)
		printf("\033[32m[OK]\033[0m\n");
	else
		printf("\033[31m[KO]\033[0m\n");
}

void test_ft_isalpha()
{
	printf("\n--- Testing ft_isalpha ---\n");
	printf("'a': "); print_result(ft_isalpha('a') && isalpha('a'));
	printf("'Z': "); print_result(ft_isalpha('Z') && isalpha('Z'));
	printf("'5': "); print_result(!ft_isalpha('5') && !isalpha('5'));
	printf("' ': "); print_result(!ft_isalpha(' ') && !isalpha(' '));
	printf("EOF (-1): "); print_result(!ft_isalpha(-1) && !isalpha(-1));
}

void test_ft_isdigit()
{
	printf("\n--- Testing ft_isdigit ---\n");
	printf("'5': "); print_result(ft_isdigit('5') && isdigit('5'));
	printf("'0': "); print_result(ft_isdigit('0') && isdigit('0'));
	printf("'a': "); print_result(!ft_isdigit('a') && !isdigit('a'));
	printf("']': "); print_result(!ft_isdigit(']') && !isdigit(']'));
}

void test_ft_isalnum()
{
	printf("\n--- Testing ft_isalnum ---\n");
	printf("'a': "); print_result(ft_isalnum('a') && isalnum('a'));
	printf("'7': "); print_result(ft_isalnum('7') && isalnum('7'));
	printf("'*': "); print_result(!ft_isalnum('*') && !isalnum('*'));
}

void test_ft_isascii()
{
	printf("\n--- Testing ft_isascii ---\n");
	printf("127: "); print_result(ft_isascii(127) && isascii(127));
	printf("0: "); print_result(ft_isascii(0) && isascii(0));
	printf("128: "); print_result(!ft_isascii(128) && !isascii(128));
	printf("-1: "); print_result(!ft_isascii(-1) && !isascii(-1));
}

void test_ft_isprint()
{
	printf("\n--- Testing ft_isprint ---\n");
	printf("'~' (126): "); print_result(ft_isprint('~') && isprint('~'));
	printf("' ' (32): "); print_result(ft_isprint(' ') && isprint(' '));
	printf("DEL (127): "); print_result(!ft_isprint(127) && !isprint(127));
	printf("TAB (9): "); print_result(!ft_isprint('\t') && !isprint('\t'));
}

void test_ft_strlen()
{
	printf("\n--- Testing ft_strlen ---\n");
	const char *s1 = "Hello World!";
	const char *s2 = "";
	printf("\"%s\": ", s1); print_result(ft_strlen(s1) == strlen(s1));
	printf("Empty string: "); print_result(ft_strlen(s2) == strlen(s2));
}

void test_ft_memset()
{
	printf("\n--- Testing ft_memset ---\n");
	char b1[20], b2[20];
	ft_memset(b1, 'A', 10);
	memset(b2, 'A', 10);
	b1[10] = '\0'; b2[10] = '\0';
	printf("Set 10 'A's: "); print_result(strcmp(b1, b2) == 0);
}

void test_ft_bzero()
{
	printf("\n--- Testing ft_bzero ---\n");
	char b1[10] = "123456789";
	char b2[10] = "123456789";
	ft_bzero(b1, 5);
	bzero(b2, 5);
	printf("Zero 5 bytes: "); print_result(memcmp(b1, b2, 10) == 0);
}

void test_ft_memcpy()
{
	printf("\n--- Testing ft_memcpy ---\n");
	char src[] = "Copy This";
	char dst1[20], dst2[20];
	ft_memcpy(dst1, src, strlen(src) + 1);
	memcpy(dst2, src, strlen(src) + 1);
	printf("Copying \"%s\": ", src); print_result(strcmp(dst1, dst2) == 0);
}

void test_ft_memmove()
{
	printf("\n--- Testing ft_memmove ---\n");
	char str[] = "123456789";
	char str_ft[20] = "123456789";
	char str_std[20] = "123456789";

	// Overlap: dest > src
	ft_memmove(str_ft + 2, str_ft, 5); // 121234589
	memmove(str_std + 2, str_std, 5);
	printf("Overlap dest > src: "); print_result(strcmp(str_ft, str_std) == 0);

	// Overlap: dest < src
	strcpy(str_ft, "123456789");
	strcpy(str_std, "123456789");
	ft_memmove(str_ft, str_ft + 2, 5); // 345676789
	memmove(str_std, str_std + 2, 5);
	printf("Overlap dest < src: "); print_result(strcmp(str_ft, str_std) == 0);
}

void test_ft_strlcpy()
{
	printf("\n--- Testing ft_strlcpy ---\n");
	char dst[10];
	const char *src = "Hello World!";
	size_t res_ft = ft_strlcpy(dst, src, 10);
	size_t res_std = strlcpy(dst, src, 10); // Note: strlcpy may not be on all systems, especially Linux.
	printf("Copy 'Hello Wor' (size 10): "); print_result(strcmp(dst, "Hello Wor") == 0 && res_ft == strlen(src));
	res_ft = ft_strlcpy(dst, "OK", 10);
	printf("Copy 'OK' (size 10): "); print_result(strcmp(dst, "OK") == 0 && res_ft == 2);
}

void test_ft_strlcat()
{
	printf("\n--- Testing ft_strlcat ---\n");
	char dst[20] = "Hello";
	const char *src = ", World!";
	size_t res_ft = ft_strlcat(dst, src, 15);
	size_t expected_len = strlen("Hello") + strlen(src);
	printf("Concat 'Hello, Worl': "); print_result(strcmp(dst, "Hello, Worl") == 0 && res_ft == expected_len);
}

void test_ft_toupper_tolower()
{
	printf("\n--- Testing ft_toupper & ft_tolower ---\n");
	printf("toupper('a'): "); print_result(ft_toupper('a') == 'A');
	printf("toupper('Z'): "); print_result(ft_toupper('Z') == 'Z');
	printf("tolower('B'): "); print_result(ft_tolower('B') == 'b');
	printf("tolower('z'): "); print_result(ft_tolower('z') == 'z');
}

void test_ft_strchr_strrchr()
{
	printf("\n--- Testing ft_strchr & ft_strrchr ---\n");
	const char *s = "ab-cd-ef";
	printf("strchr 'c': "); print_result(ft_strchr(s, 'c') == strchr(s, 'c'));
	printf("strchr 'z': "); print_result(ft_strchr(s, 'z') == strchr(s, 'z'));
	printf("strchr '\\0': "); print_result(ft_strchr(s, '\0') == strchr(s, '\0'));
	printf("strrchr '-': "); print_result(ft_strrchr(s, '-') == strrchr(s, '-'));
	printf("strrchr 'a': "); print_result(ft_strrchr(s, 'a') == strrchr(s, 'a'));
}

void test_ft_strncmp()
{
	printf("\n--- Testing ft_strncmp ---\n");
	const char *s1 = "abcde";
	const char *s2 = "abcfg";
	const char *s3 = "abc";
	printf("Compare 'abcde', 'abcfg', 3: "); print_result(ft_strncmp(s1, s2, 3) == 0);
	printf("Compare 'abcde', 'abcfg', 4: "); print_result(ft_strncmp(s1, s2, 4) < 0);
	printf("Compare 'abcde', 'abc', 5: "); print_result(ft_strncmp(s1, s3, 5) > 0);
}

void test_ft_memchr()
{
	printf("\n--- Testing ft_memchr ---\n");
	const char *s = "12345";
	printf("Find '3' in '12345': "); print_result(ft_memchr(s, '3', 5) == memchr(s, '3', 5));
	printf("Find 'x' in '12345': "); print_result(ft_memchr(s, 'x', 5) == memchr(s, 'x', 5));
}

void test_ft_memcmp()
{
	printf("\n--- Testing ft_memcmp ---\n");
	const char *s1 = "abcde";
	const char *s2 = "abcfg";
	printf("memcmp 3 bytes: "); print_result(ft_memcmp(s1, s2, 3) == memcmp(s1, s2, 3));
	printf("memcmp 4 bytes: "); print_result((ft_memcmp(s1, s2, 4) < 0) == (memcmp(s1, s2, 4) < 0));
}

void test_ft_strnstr()
{
	printf("\n--- Testing ft_strnstr ---\n");
	const char *big = "Foo Bar Baz";
	const char *little = "Bar";
	printf("Find 'Bar' in 'Foo Bar Baz' (len 11): "); print_result(ft_strnstr(big, little, 11) == strnstr(big, little, 11));
	printf("Find 'Bar' in 'Foo Bar Baz' (len 6): "); print_result(ft_strnstr(big, little, 6) == NULL);
	printf("Find '' in 'Foo Bar Baz': "); print_result(ft_strnstr(big, "", 10) == big);
}

void test_ft_atoi()
{
	printf("\n--- Testing ft_atoi ---\n");
	printf("\"42\": "); print_result(ft_atoi("42") == 42);
	printf("\"   -42\": "); print_result(ft_atoi("   -42") == -42);
	printf("\"4193 with words\": "); print_result(ft_atoi("4193 with words") == 4193);
	printf("\"-91283472332\": "); print_result(ft_atoi("-91283472332") == atoi("-91283472332")); // overflow
}

void test_ft_calloc()
{
	printf("\n--- Testing ft_calloc ---\n");
	size_t count = 10;
	int *arr = ft_calloc(count, sizeof(int));
	int all_zero = 1;
	if (arr) {
		for(size_t i = 0; i < count; i++) {
			if (arr[i] != 0) {
				all_zero = 0;
				break;
			}
		}
		free(arr);
	} else {
		all_zero = 0;
	}
	printf("Allocate 10 ints and check if zero: "); print_result(all_zero);
}

void test_ft_strdup()
{
	printf("\n--- Testing ft_strdup ---\n");
	const char *s1 = "Duplicate me!";
	char *s2 = ft_strdup(s1);
	printf("Duplicate '%s': ", s1); print_result(s2 != NULL && strcmp(s1, s2) == 0);
	free(s2);
}

void test_ft_substr()
{
	printf("\n--- Testing ft_substr ---\n");
	char const *s = "hello world";
	char *sub;

	sub = ft_substr(s, 6, 5); // "world"
	printf("substr(s, 6, 5) -> 'world': "); print_result(sub && strcmp(sub, "world") == 0);
	free(sub);

	sub = ft_substr(s, 20, 5); // start out of bounds
	printf("substr(s, 20, 5) -> '': "); print_result(sub && strcmp(sub, "") == 0);
	free(sub);

	sub = ft_substr(s, 6, 100); // len too long
	printf("substr(s, 6, 100) -> 'world': "); print_result(sub && strcmp(sub, "world") == 0);
	free(sub);
}

void test_ft_strjoin()
{
	printf("\n--- Testing ft_strjoin ---\n");
	char *res = ft_strjoin("Hello, ", "World!");
	printf("strjoin('Hello, ', 'World!'): "); print_result(res && strcmp(res, "Hello, World!") == 0);
	free(res);
}

void test_ft_strtrim()
{
	printf("\n--- Testing ft_strtrim ---\n");
	char *res;
	res = ft_strtrim("  hello world  ", " ");
	printf("strtrim('  hello world  ', ' '): "); print_result(res && strcmp(res, "hello world") == 0);
	free(res);

	res = ft_strtrim("abchellocba", "abc");
	printf("strtrim('abchellocba', 'abc'): "); print_result(res && strcmp(res, "hello") == 0);
	free(res);
}

// ft_split için yardımcı test fonksiyonu
void print_split_array(char **arr) {
	if (!arr) {
		printf("NULL array\n");
		return;
	}
	printf("{ ");
	for (int i = 0; arr[i]; i++) {
		printf("\"%s\"", arr[i]);
		if (arr[i+1]) printf(", ");
	}
	printf(" }\n");
}

void free_split_array(char **arr) {
	if (!arr) return;
	for (int i = 0; arr[i]; i++) {
		free(arr[i]);
	}
	free(arr);
}

void test_ft_split()
{
	printf("\n--- Testing ft_split ---\n");
	char **res;
	char const *s1 = "  hello world again  ";
	printf("Splitting '%s' with ' ': ", s1);
	res = ft_split(s1, ' ');
	print_split_array(res);
	// Manuel kontrol: {"hello", "world", "again"} olmalı
	print_result(res && res[0] && res[1] && res[2] && !res[3] &&
				 strcmp(res[0], "hello") == 0 &&
				 strcmp(res[1], "world") == 0 &&
				 strcmp(res[2], "again") == 0);
	free_split_array(res);

	char const *s2 = "---split---this---";
	printf("Splitting '%s' with '-': ", s2);
	res = ft_split(s2, '-');
	print_split_array(res);
	print_result(res && res[0] && res[1] && !res[2] &&
				 strcmp(res[0], "split") == 0 &&
				 strcmp(res[1], "this") == 0);
	free_split_array(res);
}

void test_ft_itoa()
{
	printf("\n--- Testing ft_itoa ---\n");
	char *s;
	s = ft_itoa(12345);
	printf("itoa(12345): "); print_result(s && strcmp(s, "12345") == 0); free(s);
	s = ft_itoa(-12345);
	printf("itoa(-12345): "); print_result(s && strcmp(s, "-12345") == 0); free(s);
	s = ft_itoa(0);
	printf("itoa(0): "); print_result(s && strcmp(s, "0") == 0); free(s);
	s = ft_itoa(-2147483648);
	printf("itoa(-2147483648): "); print_result(s && strcmp(s, "-2147483648") == 0); free(s);
}

// strmapi ve striteri için test fonksiyonları
char charmapi_func(unsigned int i, char c) {
	(void)i; // unused
	return (c + 1);
}
void striteri_func(unsigned int i, char *c) {
	(void)i; // unused
	*c = *c + 1;
}

void test_ft_strmapi_striteri()
{
	printf("\n--- Testing ft_strmapi & ft_striteri ---\n");
	char s_mapi[] = "abc";
	char *res_mapi = ft_strmapi(s_mapi, charmapi_func);
	printf("strmapi('abc', c+1): "); print_result(res_mapi && strcmp(res_mapi, "bcd") == 0);
	free(res_mapi);

	char s_iteri[] = "abc";
	ft_striteri(s_iteri, striteri_func);
	printf("striteri('abc', c+1): "); print_result(strcmp(s_iteri, "bcd") == 0);
}

void test_ft_put_fd()
{
	printf("\n--- Testing ft_put*_fd functions ---\n");
	int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror("Failed to open test_output.txt");
		return;
	}

	// Test ft_putchar_fd
	ft_putchar_fd('A', fd);

	// Test ft_putstr_fd
	ft_putstr_fd("BC", fd);

	// Test ft_putendl_fd
	ft_putendl_fd("DE", fd); // "DE\n" yazar

	// Test ft_putnbr_fd
	ft_putnbr_fd(-123, fd);

	close(fd);

	// Şimdi dosyayı okuyup içeriği kontrol edelim
	fd = open("test_output.txt", O_RDONLY);
	char buffer[50] = {0};
	read(fd, buffer, 49);
	close(fd);

	const char *expected = "ABCDE\n-123";
	printf("put*_fd functions combined: ");
	print_result(strcmp(buffer, expected) == 0);
	printf("    (Check 'test_output.txt' file for content: \"%s\")\n", expected);
}

// ===========================================================================
//                                  ANA TEST
// ===========================================================================

int main(void)
{
	printf("=======================================\n");
	printf("      LIBFT FUNCTION TEST SUITE\n");
	printf("=======================================\n");

	// Part 1
	// test_ft_isalpha();
	// test_ft_isdigit();
	// test_ft_isalnum();
	// test_ft_isascii();
	// test_ft_isprint();
	// test_ft_strlen();
	// test_ft_memset();
	// test_ft_bzero();
	// test_ft_memcpy();
	// test_ft_memmove();
	// test_ft_strlcpy();
	// test_ft_strlcat();
	// test_ft_toupper_tolower();
	test_ft_strchr_strrchr();
	// test_ft_strncmp();
	// test_ft_memchr();
	// test_ft_memcmp();
	// test_ft_strnstr();
	// test_ft_atoi();
	// test_ft_calloc();
	// test_ft_strdup();

	// // Part 2
	// test_ft_substr();
	// test_ft_strjoin();
	// test_ft_strtrim();
	// test_ft_split();
	// test_ft_itoa();
	// test_ft_strmapi_striteri();
	// test_ft_put_fd();

	printf("\n--- All tests completed. ---\n");
	return (0);
}
