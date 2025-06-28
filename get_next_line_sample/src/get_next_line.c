/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:17:40 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/28 16:17:41 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/get_next_line.h"

// get_next_line fonksiyonu, fd'den bir satır okur ve döndürür.
// Okuma işlemi için static bir stash (bağlı liste) kullanılır.
char	*get_next_line(int fd)
{
	static t_list	*stash = NULL; // Okunan verileri tutan static bağlı liste
	char			*line;

	// Geçersiz fd veya buffer kontrolü, ayrıca read ile fd kontrolü
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;

	// 1. Dosyadan oku ve stash'e ekle
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);

	// 2. Stash'ten satırı çıkar
	extract_line(stash, &line);

	// 3. Kullanılan kısmı stash'ten temizle
	clean_stash(&stash);

	// Eğer satır boşsa (EOF veya hata), belleği temizle ve NULL döndür
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

// Dosyadan BUFFER_SIZE kadar okuma yapar ve okunan veriyi stash'e ekler.
// Satır sonu (\n) bulunana kadar veya dosya bitene kadar devam eder.
void	read_and_stash(int fd, t_list **stash)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1)); // Okuma buffer'ı
		if (buf == NULL)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE); // Dosyadan oku
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0'; // Buffer'ı null-terminatörle bitir
		add_to_stash(stash, buf, readed); // Buffer'ı stash'e ekle
		free(buf);
	}
}

// Okunan buffer'ı stash'in sonuna ekler.
// Her okuma işlemi için yeni bir düğüm oluşturulur.
void	add_to_stash(t_list **stash, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list)); // Yeni düğüm oluştur
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1)); // İçerik için yer ayır
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash); // Listenin sonuna ekle
	last->next = new_node;
}

// Stash'ten bir satırı (\n dahil) line'a kopyalar.
// Satır sonuna kadar tüm karakterleri birleştirir.
void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash); // Satır için yeterli alan ayır
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i]; // Satır sonunu da ekle
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0'; // Satırı null-terminatörle bitir
}

// Satır döndürüldükten sonra, stash'te kalan kullanılmamış karakterleri tutar.
// Kullanılan düğümleri ve içerikleri serbest bırakır, sadece kalan kısmı yeni bir düğümde saklar.
void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list)); // Yeni düğüm oluştur
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash); // Son düğümü bul
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1)); // Kalan karakterler için yer ayır
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash); // Eski stash'i temizle
	*stash = clean_node;
}
