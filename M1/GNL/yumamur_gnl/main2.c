#include "get_next_line_bonus.h" // get_next_line fonksiyonunun bonus sürümü için header
#include <stdio.h>                  // printf için
#include <fcntl.h>                  // open fonksiyonu için

int main()
{
    int fd = open("get_next_line.c", O_RDONLY); // get_next_line.c dosyasını sadece okuma modunda aç
    char *tmp;
    int i = 0;

    // 29 satır boyunca dosyadan satır oku ve belleği serbest bırak
    while (1)
    {
        i++;
        if(i == 29)
            break; // 29. satırda döngüden çık
        tmp = get_next_line(fd); // Bir satır oku
        free(tmp);               // Okunan satırı serbest bırak
    }
    tmp = get_next_line(fd);     // 30. satırı oku
    printf("%s", tmp);           // 30. satırı ekrana yazdır
    free(tmp);                   // Son satırı da serbest bırak
}
