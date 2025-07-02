/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:16:32 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/02 12:57:42 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // Bellek yönetimi için gerekli

# include <sys/types.h> // read fonksiyonu için gerekli
# include <sys/uio.h>   // read fonksiyonu için gerekli
# include <unistd.h>    // read ve close fonksiyonları için gerekli

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 // Okuma işlemlerinde kullanılacak buffer boyutu, default 5
# endif

// Okunan verileri satır satır biriktirmek için kullanılan bağlı liste yapısı
typedef struct	s_list
{
	char			*content; // Okunan verinin bir parçası (buffer)
	struct s_list	*next;   // Sonraki düğüme işaretçi
}t_list;

// Dosya tanımlayıcısından bir satır okur ve döndürür
char	*get_next_line(int fd);

// Stash'te (bağlı listede) yeni satır karakteri var mı kontrol eder
int 	found_newline(t_list *stash);

// Stash'in (bağlı listenin) son düğümünü döndürür
t_list	*ft_lst_get_last(t_list *stash);

// Dosyadan okuma yapar ve okunan veriyi stash'e ekler
void	read_and_stash(int fd, t_list **stash);

// Okunan buffer'ı stash'e ekler
void	add_to_stash(t_list **stash, char *buf, int readed);

// Stash'ten bir satırı çıkarır (satır sonuna kadar olan kısmı line'a kopyalar)
void	extract_line(t_list *stash, char **line);

// Stash'ten line oluşturur (satırın tamamını birleştirir)
void	generate_line(char **line, t_list *stash);

// Satırı döndürdükten sonra stash'i temizler (kullanılan kısmı siler)
void	clean_stash(t_list **stash);

// String uzunluğunu hesaplar (kendi ft_strlen fonksiyonu)
int 	ft_strlen(const char *str);

// Stash'teki tüm düğümleri ve içeriklerini serbest bırakır
void	free_stash(t_list *stash);

#endif