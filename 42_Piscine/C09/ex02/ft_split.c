/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:26:35 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/21 14:28:46 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Çalışma Mantığı:
is_sep: Karakterin ayraç olup olmadığını kontrol eder.
count_words: Kelime sayısını hesaplar.
fill_arr:
	Kelimeleri bulur
	Bellek ayırır
	Karakterleri kopyalar
	Hata durumunda free_mem çağırır
free_mem: Hata durumunda önceki bellekleri temizler.*/

#include <stdlib.h>

int	is_sep(char c, char *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!is_sep(str[i], charset))
		{
			if (!str[i + 1] || is_sep(str[i + 1], charset))
				count++;
		}
		i++;
	}
	return (count);
}

char	**free_mem(char **arr, int size)
{
	while (size-- > 0)
		free(arr[size]);
	free(arr);
	return (0);
}

char	**fill_arr(char *s, char *set, char **arr, int wc)
{
	int	i;
	int	len;

	i = -1;
	while (++i < wc)
	{
		while (*s && is_sep(*s, set))
			s++;
		len = 0;
		while (s[len] && !is_sep(s[len], set))
			len++;
		arr[i] = (char *)malloc(len + 1);
		if (!arr[i])
			return (free_mem(arr, i));
		len = -1;
		while (++len, s[len] && !is_sep(s[len], set))
			arr[i][len] = s[len];
		arr[i][len] = 0;
		s += len;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(char *str, char *charset)
{
	char	**result;
	int		word_count;

	if (!str || !charset)
		return (0);
	word_count = count_words(str, charset);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (0);
	if (!fill_arr(str, charset, result, word_count))
		return (0);
	return (result);
}
/* 
#include <stdio.h>

int	main(void)
{
	// Bölünecek orijinal string.
	char	*str = "Merhaba, nasılsınız? Bugün hava çok güzel.";
	// Ayraç karakterler: boşluk, virgül, soru işareti ve nokta.
	char	*charset = " ,?.";
	char	**result;  // ft_split fonksiyonundan dönecek kelimeler dizisi.
	int		i;

	
	result = ft_split(str, charset);
	if (!result)  // Bellek hatası kontrolü.
	{
		printf("Bellek hatası!\n");
		return (1);
	}

	// result dizisinde bulunan her kelimeyi ekrana yazdır.
	i = 0;
	while (result[i])
	{
		printf("Kelime %d: %s\n", i, result[i]);
		free(result[i]);  // Her kelime için ayrılan belleği serbest bırak.
		i++;
	}
	free(result);  // Kelimeleri saklayan ana diziyi serbest bırak.
	return (0);
} */