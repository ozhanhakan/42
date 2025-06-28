/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:59:04 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/28 21:59:07 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

// Bu statik dizi, "global değişken" yasağını ihlal etmez. 
// Kapsamı bu dosya ile sınırlıdır ve projenin amacı static değişkenleri
// öğretmektir. 
// Aynı anda birden fazla dosyayı yönetir. [cite: 52]
static char	*stash[MAX_FD];

static char	*read_from_fd(int fd, char *current_stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(current_stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(current_stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		current_stash = ft_strjoin_and_free(current_stash, buffer);
		if (!current_stash)
			break ;
	}
	free(buffer);
	return (current_stash);
}

static char	*extract_line(char *full_stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!full_stash[i])
		return (NULL);
	while (full_stash[i] && full_stash[i] != '\n')
		i++;
	// Satır, \n karakterini de içermelidir. 
	if (full_stash[i] == '\n')
		i++;
	line = ft_substr(full_stash, 0, i);
	return (line);
}

static char	*update_stash(char *old_stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (old_stash[i] && old_stash[i] != '\n')
		i++;
	if (old_stash[i] == '\n')
		i++;
	if (!old_stash[i])
	{
		free(old_stash);
		return (NULL);
	}
	new_stash = ft_strdup(&old_stash[i]);
	free(old_stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	stash[fd] = read_from_fd(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = update_stash(stash[fd]);
	// Eğer extract_line sonucu boş bir string geldiyse (EOF'ta olabilir),
	// bunu NULL'a çevirmemek gerekir, boş bir satır olabilir.
	if (line && !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}