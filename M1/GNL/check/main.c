#include "get_next_line.h" // Fonksiyon prototipleri ve yardımcılar
#include <fcntl.h>          // open fonksiyonu için (dosya açma)
#include <stdio.h>          // printf fonksiyonu için (ekrana yazdırma)

// Temel test main'i: test.txt dosyasını satır satır okur ve ekrana yazar.
int test2(void);

int main(void)
{
    int fd = open("test.txt", O_RDONLY); // test.txt dosyasını okuma modunda aç
    char *line=NULL; // Okunan satırı tutacak pointer
     line = get_next_line(fd);
    while (!line) // Satır satır oku
    {   
    
            printf("%s", line); // Satırı ekrana yazdır
            free(line);         // Belleği serbest bırak
         
       line = get_next_line(fd);
    }
    //printf("\nmain fd: %d\n", fd); // Dosya tanımlayıcısını ekrana yazdır
    close(fd); // Dosyayı kapat
    
    //int fd2 = open("test.txt", O_RDONLY); // test.txt dosyasını okuma modunda aç
    //printf("\nmain fd: %d\n", fd2); // Dosya tanımlayıcısını ekrana yazdır
    //close(fd2); // Dosyayı kapat
    

    test2();
    //close(fd); // Dosyayı kapat
//    printf("\nmain fd: after close %d\n", fd); // Dosya tanımlayıcısını ekrana yazdır
    //close(fd2); // Dosyayı kapat
    // close(fd3); // Dosyayı kapat
    
    return 0; // Programı başarılı şekilde sonlandır
}
int test2(void)
{
    int fd = open("test1.txt", O_RDONLY);
    char *line;
    line = get_next_line(fd);
    printf("\nmain2 fd: %d\n", fd); // Dosya tanımlayıcısını ekrana yazdır

    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    
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
