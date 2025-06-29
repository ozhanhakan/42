// Dosya Adı: main.c

#include "get_next_line.h"
#include <fcntl.h>  // open için
#include <stdio.h>  // printf için

int main(void)
{
	int		fd;
	char	*line;

	// Okunacak test dosyasını aç (sadece okuma modunda)
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Hata: test.txt dosyasi acilamadi.\n");
		return (1);
	}

	printf("--- test.txt dosyasinin icerigi ---\n");
	// Dosyanın sonuna gelene kadar satır satır oku ve yazdır
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); // GNL'den dönen satırı free'lemeyi unutma!
	}
	printf("--- Dosya sonu ---\n");

	close(fd);
	return (0);
}