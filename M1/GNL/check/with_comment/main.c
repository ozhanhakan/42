#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// Basit test main'i: test.txt dosyasını satır satır okur ve ekrana yazar.
int main(void)
{
    int fd = open("test.txt", O_RDONLY); // test.txt dosyasını okuma modunda aç
    char *line;
    while ((line = get_next_line(fd))) // Satır satır oku
    {
        printf("%s", line); // Satırı ekrana yazdır
        free(line);         // Belleği serbest bırak
    }
    close(fd); // Dosyayı kapat
    return 0;
}
