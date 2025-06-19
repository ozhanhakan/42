#include <stdio.h>   // For printf (test çıktısı için)
#include <unistd.h>  // For STDOUT_FILENO, STDERR_FILENO, close, open, read
#include <fcntl.h>   // For O_CREAT, O_WRONLY, O_APPEND, O_RDONLY
#include <string.h>  // For strcmp, strlen (doğrulama için)
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_putstr_fd function prototype (if not in libft.h or commented out)
// void ft_putstr_fd(char *s, int fd);
// ft_strlen function prototype (if not in libft.h or commented out, needed for test validation)
// size_t ft_strlen(const char *s);

// --- Yardımcı Test Fonksiyonu (Konsol Çıktısı İçin) ---
void test_putstr_fd_console(char *s, int fd, const char *description, int test_num)
{
    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Yazılacak String: \"%s\"\n", s ? s : "(NULL)");
    printf("  Sonuç: (Alttaki satırda string görünmeli)\n");
    ft_putstr_fd(s, fd); // ft_putstr_fd'yi çağır
    printf("\n"); // Sonraki çıktıları ayırmak için yeni satır
    printf("  Durum: Manuel Onay Gerekiyor.\n\n");
}

// --- Dosya Testi Yardımcı Fonksiyonu (Gözlemlenebilir) ---
// Dosyayı silmez ve her çalıştırdığınızda üzerine eklemeye devam eder.
void test_putstr_fd_file(char *s, const char *filename, const char *description, int test_num)
{
    int     fd;

    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Yazılacak String: \"%s\"\n", s ? s : "(NULL)");
    printf("  Hedef Dosya: \"%s\"\n", filename);

    // Dosyayı oluşturma/açma (yazma modunda, mevcutsa sona ekle, yoksa oluştur)
    fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("Error opening file for test");
        printf("  Durum: BAŞARISIZ (Dosya açılamadı).\n\n");
        return;
    }

    // Stringi dosyaya yazma
    ft_putstr_fd(s, fd);
    close(fd);

    printf("  Dosyaya \"%s\" stringi eklendi.\n", s ? s : "(NULL)");
    printf("  Dosyanın mevcut içeriğini manuel olarak kontrol edebilirsiniz.\n");
    printf("  Durum: GÖZLEM (Dosya silinmeyecek ve üzerine eklenecek.)\n\n");
}


// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_putstr_fd Testleri ---\n\n");

    // Konsol çıktı testleri
    test_putstr_fd_console("Hello World!", STDOUT_FILENO, "Standart Ciktiya String Yazma", 1);
    test_putstr_fd_console("Bu bir hata mesajidir.\n", STDERR_FILENO, "Standart Hataya String Yazma", 2);
    test_putstr_fd_console("", STDOUT_FILENO, "Bos String Yazma", 3);
    test_putstr_fd_console("Tek Satir\nIkinci Satir", STDOUT_FILENO, "Cok Satirli String Yazma", 4);

    // Dosyaya çıktı testleri (gözlemlenebilir)
    test_putstr_fd_file("LOG: Program basladi.\n", "app_log.txt", "Dosyaya Log Mesaji Ekleme", 5);
    test_putstr_fd_file("LOG: Islem tamamlandi.\n", "app_log.txt", "Dosyaya Devam Log Mesaji Ekleme", 6);
    test_putstr_fd_file("KISA ", "kisa_log.txt", "Kisa string ekleme (1)", 7);
    test_putstr_fd_file("LOG", "kisa_log.txt", "Kisa string ekleme (2)", 8);
    test_putstr_fd_file(NULL, "app_log.txt", "NULL stringi yazma (hicbir sey yapmamali)", 9); // NULL kontrolü

    return 0;
}
