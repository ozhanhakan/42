#include "get_next_line_bonus.h" // Bonus fonksiyon prototipleri ve yardımcılar
#include <fcntl.h>                // open fonksiyonu için (dosya açma)
#include <stdio.h>                // printf fonksiyonu için (ekrana yazdırma)

// Bonus test main'i: Aynı anda iki dosyadan satır satır okuma örneği
int main(void)
{
    int fd1 = open("test1.txt", O_RDONLY); // test1.txt dosyasını sadece okuma modunda açar
    int fd2 = open("test2.txt", O_RDONLY); // test2.txt dosyasını sadece okuma modunda açar
    char *line1; // fd1'den okunan satırı tutacak pointer
    char *line2; // fd2'den okunan satırı tutacak pointer
    int i = 0;   // Döngü sayacı
    while (i < 5) // 5 kez döner, her iki dosyadan 5 satır okur
    {
        line1 = get_next_line(fd1); // fd1'den bir satır oku
        line2 = get_next_line(fd2); // fd2'den bir satır oku
        printf("fd1: %s", line1);   // fd1'den okunan satırı ekrana yazdır
        printf("fd2: %s", line2);   // fd2'den okunan satırı ekrana yazdır
        free(line1);                // Okunan satırın belleğini serbest bırak
        free(line2);                // Okunan satırın belleğini serbest bırak
        i++;                        // Sayaç artır
    }
    close(fd1); // fd1 dosya tanımlayıcısını kapat
    close(fd2); // fd2 dosya tanımlayıcısını kapat
    return 0;   // Programı başarılı şekilde sonlandır
}

/*
Kullanılan keywordler ve açıklamaları:
- #include: Başka bir dosyanın içeriğini bu dosyaya ekler.
- int: Tam sayı veri tipi.
- char *: Karakter dizisi (string) için pointer.
- void: Fonksiyonun dönüş tipi yok anlamında.
- return: Fonksiyondan çıkış ve değer döndürme.
- while: Koşullu döngü başlatır.
- printf: Ekrana çıktı verir.
- open: Dosya açar, dosya tanımlayıcısı döndürür.
- close: Dosya tanımlayıcısını kapatır.
- free: malloc ile ayrılan belleği serbest bırakır.
*/
