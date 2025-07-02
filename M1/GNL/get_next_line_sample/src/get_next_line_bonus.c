#include "../include/get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*stash[4096];
	char		*line;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_stash(fd, &stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	extract_line(stash[fd], &line);
	clean_stash(&stash[fd]);
	if (line == NULL || line[0] == '\0')
	{
		free_stash(stash[fd]);
		stash[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

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
