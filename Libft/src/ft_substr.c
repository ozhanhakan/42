/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:55:47 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/16 14:37:25 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen ve gerekirse ft_strlcpy için
#include <stdlib.h> // malloc için
#include <stddef.h> // size_t için

/*
Allocates memory (using malloc(3)) and returns a
substring from the string ’s’.
The substring starts at index ’start’ and has a
maximum length of ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
    char            *sub;
    size_t          s_len;
    size_t          actual_len; // Gerçekte kopyalanacak karakter sayısı
    size_t          i;          // Döngü sayacı

    if (!s) // 1. Olası hata: Giriş string'i NULL ise
        return (NULL);

    s_len = ft_strlen(s);

    // 2. Olası hata: 'start' indeksi string'in uzunluğundan büyük veya eşitse
    // Bu durumda boş bir string ("") döndürülmeli.
    if (start >= s_len)
    {
        sub = (char *)malloc(sizeof(char) * 1); // Boş string için 1 byte ayır
        if (!sub) // Bellek ayırma hatası kontrolü
            return (NULL);
        sub[0] = '\0'; // Boş string'i null sonlandır
        return (sub);
    }

    // 3. Olası hata: 'len' parametresi çok büyükse veya 'start' sonrası string'in kalan kısmı 'len'den küçükse.
    // Gerçekte kopyalanması gereken uzunluğu hesapla.
    // Ya istenen 'len' kadar kopyalanır, ya da string'in sonuna kadar kalan kısım (s_len - start).
    if (len > s_len - start)
        actual_len = s_len - start;
    else
        actual_len = len;

    // Bellek ayır: 'actual_len' kadar karakter + null sonlandırıcı için 1 byte.
    sub = (char *)malloc(sizeof(char) * (actual_len + 1));
    if (!sub) // Bellek ayırma hatası kontrolü
        return (NULL);

    // Karakterleri kopyala
    i = 0;
    while (i < actual_len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0'; // Kopyalanan alt string'i null sonlandır

    return (sub);
}
