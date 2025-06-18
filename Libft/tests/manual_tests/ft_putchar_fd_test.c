#include "../../src/libft.h"

//test 4 dosya ekleme
#include <stdio.h>   // For printf (test çıktısı için)
#include <unistd.h>  // For close, open, read
#include <fcntl.h>   // For O_CREAT, O_WRONLY, O_APPEND, O_RDONLY
#include <string.h>  // For strcmp (bu testte kullanılmasa da genel pratik için bırakılabilir)

// #include "libft.h" // Kendi libft.h dosyanızı buraya dahil etmeyi unutmayın!

// ft_putchar_fd function prototype (if not in libft.h or commented out)
// void ft_putchar_fd(char c, int fd);

// --- Dosya Testi Yardımcı Fonksiyonu ---
// Bu fonksiyon bir dosyaya yazma işlemini gerçekleştirir ve okuyarak doğrular.
// Dosyayı silmez ve her çalıştırdığınızda üzerine eklemeye devam eder.
void test_putchar_fd_file(char c, const char *filename, const char *description)
{
    int     fd;
    // char    buffer[2]; // Karakter + null terminator için 2 byte -- BU SATIR KALDIRILDI
    // ssize_t bytes_read; // Okunan byte sayısını tutar -- BU SATIR KALDIRILDI

    printf("--- Test: %s ---\n", description);
    printf("  Yazılacak Karakter: '%c'\n", c);
    printf("  Hedef Dosya: \"%s\"\n", filename);

    // Dosyayı oluşturma/açma (yazma modunda, mevcutsa sona ekle, yoksa oluştur)
    // O_APPEND: Dosya varsa, yazma işlemi dosyanın sonundan başlar.
    // 0644 izinleri: Sahibi oku/yaz, grup ve diğerleri sadece oku.
    fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) // Dosya açılamazsa hata kontrolü
    {
        perror("Error opening file for test"); // Hata mesajını yazdır
        printf("  Durum: BAŞARISIZ (Dosya açılamadı).\n\n");
        return; // Fonksiyondan çık
    }

    // Karakteri dosyaya yazma
    // ft_putchar_fd fonksiyonunu kullanarak 'c' karakterini açılan 'fd'ye yazar.
    ft_putchar_fd(c, fd);
    close(fd); // Dosya tanımlayıcısını kapatmak çok önemli!

    // Dosyayı okuma modunda tekrar açma ve içeriği doğrulama
    // (Bu kısım artık aktif değil, sadece gözlemleme amaçlı bilgi mesajı veriliyor)
    printf("  Dosyaya '%c' karakteri eklendi.\n", c);
    printf("  Dosyanın mevcut içeriğini manuel olarak kontrol edebilirsiniz.\n");
    printf("  Durum: GÖZLEM (Dosya silinmeyecek ve üzerine eklenecek.)\n\n");
}


// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_putchar_fd Gözlemlenebilir Dosya Testi ---\n\n");

    // Sadece bir dosyaya yazma örneği
    // Her çalıştırıldığında, 'observable_char.txt' dosyasına bir 'C' karakteri daha eklenecek.
    // Programı birden çok kez çalıştırarak dosya boyutunun arttığını ve içeriğin değiştiğini gözlemleyebilirsiniz.
    test_putchar_fd_file('C', "observable_char.txt", "Dosyaya Karakter Ekleme ve Gözlemleme");

    return 0;
}


/* 
// test-3 sadece dosyaya yazma 
// #include <stdio.h>   // For printf (test çıktısı için)
// #include <unistd.h>  // For close, open, unlink, read
// #include <fcntl.h>   // For O_CREAT, O_WRONLY, O_TRUNC, O_RDONLY
// #include <string.h>  // For strcmp (bu testte kullanılmasa da genel pratik için bırakılabilir)

// #include "libft.h" // Kendi libft.h dosyanızı buraya dahil etmeyi unutmayın!

// ft_putchar_fd function prototype (if not in libft.h or commented out)
// void ft_putchar_fd(char c, int fd);

// --- Dosya Testi Yardımcı Fonksiyonu ---
// Bu fonksiyon bir dosyaya yazma işlemini gerçekleştirir ve okuyarak doğrular.
void test_putchar_fd_file(char c, const char *filename, const char *description)
{
    int     fd;
    char    buffer[2]; // Karakter + null terminator için 2 byte
    ssize_t bytes_read; // Okunan byte sayısını tutar

    printf("--- Test: %s ---\n", description);
    printf("  Yazılacak Karakter: '%c'\n", c);
    printf("  Hedef Dosya: \"%s\"\n", filename);

    // Dosyayı oluşturma/açma (yazma modunda, mevcutsa içeriğini sil, yoksa oluştur)
    // 0644 izinleri: Sahibi oku/yaz, grup ve diğerleri sadece oku.
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) // Dosya açılamazsa hata kontrolü
    {
        perror("Error opening file for test"); // Hata mesajını yazdır
        printf("  Durum: BAŞARISIZ (Dosya açılamadı).\n\n");
        return; // Fonksiyondan çık
    }

    // Karakteri dosyaya yazma
    // ft_putchar_fd fonksiyonunu kullanarak 'c' karakterini açılan 'fd'ye yazar.
    ft_putchar_fd(c, fd);
    close(fd); // Dosya tanımlayıcısını kapatmak çok önemli!

    // Dosyayı okuma modunda tekrar açma ve içeriği doğrulama
    fd = open(filename, O_RDONLY);
    if (fd == -1) // Dosya okuma modunda açılamazsa hata kontrolü
    {
        perror("Error opening file for read back"); // Hata mesajını yazdır
        printf("  Durum: BAŞARISIZ (Dosya okunamadı).\n\n");
        return; // Fonksiyondan çık
    }
    
    // Okuma tamponunu sıfırlama
    // Okuma öncesi tamponu temizlemek iyi bir pratiktir.
    buffer[0] = '\0';
    buffer[1] = '\0';

    // Dosyadan 1 byte okuma
    bytes_read = read(fd, buffer, 1); // buffer'a maksimum 1 byte oku
    close(fd); // Dosya tanımlayıcısını kapat

    // Test dosyasını silme (temizlik için)
    // Bu, her test çalıştığında yeni bir başlangıç sağlar.
    unlink(filename);

    // Okunan veriyi kontrol etme
    if (bytes_read == 1 && buffer[0] == c) // Eğer 1 byte okunduysa ve okunan karakter beklenense
    {
        printf("  Dosya içeriği doğru: '%c'\n", buffer[0]);
        printf("  Durum: GEÇTİ\n\n");
    }
    else // Okunan veri beklenenle eşleşmezse hata
    {
        printf("  Dosya içeriği hatalı. Okunan byte: %zd, Karakter: '%c' (Beklenen: '%c')\n", bytes_read, buffer[0], c);
        printf("  Durum: BAŞARISIZ\n\n");
    }
}


// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_putchar_fd Minimal Dosya Testi ---\n\n");

    // Sadece bir dosyaya yazma örneği
    // Bu test çalıştırıldığında, 'observable_char.txt' adında bir dosya oluşturulacak,
    // içine 'C' karakteri yazılacak, sonra geri okunup doğrulanacak ve silinecek.
    // Siz bu dosyayı oluşturulduğu anda gözlemleyebilir (ancak hızlı davranmanız gerekir),
    // ve içeriğini kontrol edebilirsiniz.
    test_putchar_fd_file('C', "observable_char.txt", "Dosyaya Karakter Yazma ve Doğrulama");

    return 0;
}
 */

/* 
// --- Yardımcı Test Fonksiyonu ---
// Bu fonksiyon standart çıktı veya hata çıktıları için görsel manuel onay gerektirir.
void test_putchar_fd_console(char c, int fd, const char *description)
{
    printf("--- Test: %s ---\n", description);
    printf("  Yazılacak Karakter: '%c'\n", c);
    printf("  Sonuç: (Alttaki satırda '%c' karakteri görünmeli)\n", c);
    ft_putchar_fd(c, fd);
    printf("\n"); // Sonraki çıktıları ayırmak için yeni satır
    printf("  Durum: Manuel Onay Gerekiyor.\n\n");
}

// --- Dosya Testi Yardımcı Fonksiyonu ---
// Bu fonksiyon bir dosyaya yazma işlemini gerçekleştirir ve okuyarak doğrular.
void test_putchar_fd_file(char c, const char *filename, const char *description)
{
    int     fd;
    char    buffer[2]; // Karakter + null terminator
    ssize_t bytes_read;

    printf("--- Test: %s ---\n", description);
    printf("  Yazılacak Karakter: '%c'\n", c);
    printf("  Hedef Dosya: \"%s\"\n", filename);

    // Dosyayı oluştur/aç (yazma modunda, mevcutsa sil, yoksa oluştur)
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file for test");
        printf("  Durum: BAŞARISIZ (Dosya açılamadı).\n\n");
        return;
    }

    // Karakteri dosyaya yaz
    ft_putchar_fd(c, fd);
    close(fd);

    // Dosyayı oku ve içeriği kontrol et
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file for read back");
        printf("  Durum: BAŞARISIZ (Dosya okunamadı).\n\n");
        return;
    }
    
    // Tamponu sıfırla
    buffer[0] = '\0';
    buffer[1] = '\0';

    bytes_read = read(fd, buffer, 1); // Sadece 1 byte oku
    close(fd);

    // Test dosyasını sil
    unlink(filename);

    if (bytes_read == 1 && buffer[0] == c)
    {
        printf("  Dosya içeriği doğru: '%c'\n", buffer[0]);
        printf("  Durum: GEÇTİ\n\n");
    }
    else
    {
        printf("  Dosya içeriği hatalı. Okunan byte: %zd, Karakter: '%c' (Beklenen: '%c')\n", bytes_read, buffer[0], c);
        printf("  Durum: BAŞARISIZ\n\n");
    }
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_putchar_fd Minimal Testler ---\n\n");

    // Ekrana yazma örneği (stdout)
    test_putchar_fd_console('K', STDOUT_FILENO, "Ekrana tek karakter yazma");

    // Dosyaya yazma örneği
    test_putchar_fd_file('Z', "minimal_output.txt", "Dosyaya tek karakter yazma");

    return 0;
}
 */

/* 
// --- Yardımcı Test Fonksiyonu ---
void test_putchar_fd(char c, int fd, const char *description, int test_num)
{
    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Yazılacak Karakter: '%c'\n", c);

    printf("  Sonuç:\n");
    // ft_putchar_fd'yi çağırıyoruz
    // Çıktı doğrudan konsola veya dosyaya gideceği için burada manuel kontrol edeceğiz
    printf("    "); // Çıktıyı görsel olarak ayırmak için
    ft_putchar_fd(c, fd);
    printf("\n"); // Yeni satır, sonraki printf'i karıştırmamak için

    printf("  Durum: Manuel Onay Gerekiyor.\n\n");
}

// --- Dosya Testi Yardımcı Fonksiyonu ---
void test_file_output(char c, const char *filename, const char *description, int test_num)
{
    int     fd;
    char    buffer[2]; // Karakter + null terminator
    ssize_t bytes_read;

    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Yazılacak Karakter: '%c'\n", c);
    printf("  Hedef Dosya: \"%s\"\n", filename);

    // Dosyayı oluştur/aç (yazma modunda, mevcutsa sil, yoksa oluştur)
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file for test");
        printf("  Durum: BAŞARISIZ (Dosya açılamadı).\n\n");
        return;
    }

    // Karakteri dosyaya yaz
    ft_putchar_fd(c, fd);
    close(fd);

    // Dosyayı oku ve içeriği kontrol et
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file for read back");
        printf("  Durum: BAŞARISIZ (Dosya okunamadı).\n\n");
        return;
    }
    
    // Tamponu sıfırla
    buffer[0] = '\0';
    buffer[1] = '\0';

    bytes_read = read(fd, buffer, 1); // Sadece 1 byte oku
    close(fd);

    // Test dosyasını sil
    unlink(filename);

    if (bytes_read == 1 && buffer[0] == c)
    {
        printf("  Dosya içeriği doğru: '%c'\n", buffer[0]);
        printf("  Durum: GEÇTİ\n\n");
    }
    else
    {
        printf("  Dosya içeriği hatalı. Okunan byte: %zd, Karakter: '%c' (Beklenen: '%c')\n", bytes_read, buffer[0], c);
        printf("  Durum: BAŞARISIZ\n\n");
    }
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_putchar_fd Testleri ---\n\n");

    // Test 1: Standart çıktıya (ekrana) karakter yazma
    test_putchar_fd('H', STDOUT_FILENO, "Standart Ciktiya Karakter Yazma (H)", 1);
    test_putchar_fd('!', STDOUT_FILENO, "Standart Ciktiya Karakter Yazma (!)", 2);
    test_putchar_fd('\n', STDOUT_FILENO, "Standart Ciktiya Yeni Satir Yazma", 3);

    // Test 4: Standart hataya karakter yazma
    test_putchar_fd('E', STDERR_FILENO, "Standart Hataya Karakter Yazma (E)", 4);
    test_putchar_fd('R', STDERR_FILENO, "Standart Hataya Karakter Yazma (R)", 5);
    test_putchar_fd('R', STDERR_FILENO, "Standart Hataya Karakter Yazma (R)", 6);

    // Test 7: Bir dosyaya karakter yazma
    test_file_output('X', "output_test_char.txt", "Dosyaya Karakter Yazma (X)", 7);
    test_file_output('5', "output_test_digit.txt", "Dosyaya Rakam Yazma (5)", 8);
    test_file_output('\n', "output_test_newline.txt", "Dosyaya Yeni Satir Yazma", 9);

    // Not: write fonksiyonu -1 döndürdüğünde hata kontrolü ft_putchar_fd'nin sorumluluğunda değildir.
    // ft_putchar_fd sadece write çağrısı yapar.

    return 0;
}
 */