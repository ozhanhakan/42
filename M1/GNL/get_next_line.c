/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 08:49:59 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/09 14:28:10 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void * ft_free(char **ptr)
{
	if (!*ptr)
		free(*ptr); // Eğer ptr NULL ise, free et
	return (NULL);
}
// Dosyadan satır sonuna kadar okuma ve eski stash ile birleştirme
// NULL check'ler kritik: malloc, read, strjoin işlemlerinde her zaman kontrol edilmeli
static char	*read_to_newline(int fd, char *old_stash)
{
	char	*buf;
	int		bytes;

	buf = malloc(BUFFER_SIZE + 1); // Okuma için buffer ayır
	if (!buf)
		{
			if(old_stash) // Eski stash varsa serbest bırak		
				free(old_stash); // Bellek sızıntısını önlemek için eski stash'i de free et
			return (NULL); // Eğer malloc başarısızsa NULL dön
		} // malloc başarısızsa NULL dön
	bytes = 1;
	// Satır sonu bulunana veya dosya bitene kadar oku
	while (bytes > 0 && !ft_strchr(old_stash, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE); // Dosyadan oku
		if (bytes == -1) // Okuma hatası
		{
			free(buf);
			free(old_stash); // Bellek sızıntısını önlemek için eski stash'i de free et
			return (NULL);
		}
		buf[bytes] = '\0'; // Okunan veriyi null-terminate et
		old_stash = ft_strjoin_and_free(old_stash, buf); // Okunanı eski stash ile birleştir
		// NULL check: malloc veya strjoin başarısızsa leak ve segfault'u önler
		if (!old_stash)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf); // Okuma buffer'ını serbest bırak
	return (old_stash); // Satır sonuna kadar okunan veriyi döndür
}

// Stash'ten bir satırı ayıkla (satır sonu dahil)
// NULL check: full_stash yoksa veya boşsa hemen NULL dönülmeli
static char	*extract_line(char *full_stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!full_stash || !full_stash[0]) // NULL veya boş stash için erken çıkış
		return (NULL);
	while (full_stash[i] && full_stash[i] != '\n') // Satır sonuna kadar ilerle
		i++;
	if (full_stash[i] == '\n') // Satır sonunu da dahil et
		i++;
	line = malloc(i + 1); // Satır için yer ayır
	if (!line)
		return (NULL); // malloc başarısızsa NULL dön
	while (j < i)
	{
		line[j] = full_stash[j]; // Satırı kopyala
		j++;
	}
	line[i] = '\0'; // Null-terminate et TODO: substr kullan, stash update et.
	return (line); // Satırı döndür
}

// Stash'ten döndürülen satırdan sonrasını yeni stash olarak ayıkla
// NULL check: full_stash yoksa veya satır sonu yoksa hemen NULL dönülmeli
static char	*update_stash(char *full_stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	if (!full_stash)
		return (NULL); // NULL stash için erken çıkış
	while (full_stash[i] && full_stash[i] != '\n') // Satır sonuna kadar ilerle
		i++;
	if (!full_stash[i]) // Satır sonu yoksa, stash'i temizle
	{
		free(full_stash);
		return (NULL);
	}
	i++; // Satır sonunu atla
	new_stash = malloc(ft_strlen(full_stash + i) + 1); // Kalan veri için yer ayır
	if (!new_stash)
		{
			free(full_stash); // Bellek sızıntısını önlemek için eski stash'i de free et
			return (NULL);
		} // malloc başarısızsa NULL dön
	while (full_stash[i])
		new_stash[j++] = full_stash[i++]; // Kalan veriyi kopyala
	new_stash[j] = '\0'; // Null-terminate et
	free(full_stash); // Eski stash'i serbest bırak
	return (new_stash); // Yeni stash'i döndür
}

// Ana fonksiyon: her çağrıda bir satır döndürür
// NULL check: her adımda malloc, okuma ve ayıklama işlemlerinde NULL kontrolü yapılmalı
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL); // Geçersiz fd veya buffer için erken çıkış
	stash = read_to_newline(fd, stash); // Satır sonuna kadar oku ve stash'i güncelle
	if (!stash)
		return (NULL); // Okuma veya birleştirme başarısızsa NULL dön
	line = extract_line(stash); // Bir satır ayıkla
	if (!line)
	{
		free(stash); // Bellek sızıntısını önle
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash); // Kalan veriyi stash'e kaydet
	return (line); // Satırı döndür
}
