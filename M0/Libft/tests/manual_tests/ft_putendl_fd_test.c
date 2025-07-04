#include <stdio.h>   // For printf (test çıktısı için)
#include <unistd.h>  // For STDOUT_FILENO, STDERR_FILENO, close, open, read
#include <fcntl.h>   // For O_CREAT, O_WRONLY, O_APPEND, O_RDONLY
#include <string.h>  // For strcmp, strlen (doğrulama için)
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_putendl_fd function prototype (if not in libft.h or commented out)
// void ft_putendl_fd(char *s, int fd);
// (ft_putstr_fd ve ft_putchar_fd de gereklidir)

// --- Yardımcı Test Fonksiyonu (Konsol Çıktısı İçin) ---
void test_putendl_fd_console(char *s, int fd, const char *description, int test_num)
{
	printf("--- Test %d: %s ---\n", test_num, description);
	printf("  Yazılacak String: \"%s\"\n", s ? s : "(NULL)");
	printf("  Sonuç: (Alttaki satırda string ve ardindan yeni satir görünmeli)\n");
	ft_putendl_fd(s, fd); // ft_putendl_fd'yi çağır
	//printf("\n"); // ft_putendl_fd zaten yeni satır eklediği için ekstra '\n' koymuyoruz.
	printf("  Durum: Manuel Onay Gerekiyor.\n\n");
}

// --- Dosya Testi Yardımcı Fonksiyonu (Gözlemlenebilir) ---
// Dosyayı silmez ve her çalıştırdığınızda üzerine eklemeye devam eder.
void test_putendl_fd_file(char *s, const char *filename, const char *description, int test_num)
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
		printf("  Durum: BAŞARISIZ (Dosya açılamadı). Lütfen 'txtfiles/' klasörünün var olduğundan emin olun.\n\n");
		return;
	}

	// Stringi ve yeni satırı dosyaya yazma
	ft_putendl_fd(s, fd);
	close(fd);

	printf("  Dosyaya \"%s\\n\" stringi eklendi.\n", s ? s : "(NULL)"); // Çıktıda \n olduğunu belirtiyoruz
	printf("  Dosyanın mevcut içeriğini '%s' konumunda manuel olarak kontrol edebilirsiniz.\n", filename);
	printf("  Durum: GÖZLEM (Dosya silinmeyecek ve üzerine eklenecek.)\n\n");
}


// --- Ana Fonksiyon ---
int main(void)
{
	const char *log_dir = "txtfiles/"; // Dosya yolu için değişken
	char full_path[256]; // Tam dosya yolu için yeterince büyük tampon

	printf("--- ft_putendl_fd Testleri ---\n\n");

	// Konsol çıktı testleri
	test_putendl_fd_console("Merhaba Dunya!", STDOUT_FILENO, "Standart Ciktiya String + Yeni Satir Yazma", 1);
	test_putendl_fd_console("Bu bir satir hatasi.", STDERR_FILENO, "Standart Hataya String + Yeni Satir Yazma", 2);
	test_putendl_fd_console("", STDOUT_FILENO, "Bos String + Yeni Satir Yazma", 3);
	char multi_line_str[] = "Ilk satir\nIkinci satir"; // ft_putendl_fd her cagridan sonra yeni satir ekler
	test_putendl_fd_console(multi_line_str, STDOUT_FILENO, "Cok Satirli String + Yeni Satir Yazma", 4);


	// Dosyaya çıktı testleri (gözlemlenebilir)
	// Lütfen bu testleri çalıştırmadan önce 'txtfiles' klasörünü manuel olarak oluşturun!
	
	snprintf(full_path, sizeof(full_path), "%s%s", log_dir, "event_log.txt");
	test_putendl_fd_file("EVENT: User logged in.", full_path, "Dosyaya Log + Yeni Satir Ekleme (1)", 5);

	snprintf(full_path, sizeof(full_path), "%s%s", log_dir, "event_log.txt");
	test_putendl_fd_file("EVENT: Data processed.", full_path, "Dosyaya Log + Yeni Satir Ekleme (2)", 6);

	snprintf(full_path, sizeof(full_path), "%s%s", log_dir, "empty_line_log.txt");
	test_putendl_fd_file("", full_path, "Dosyaya Bos Satir Ekleme", 7);

	snprintf(full_path, sizeof(full_path), "%s%s", log_dir, "null_str_log.txt");
	test_putendl_fd_file(NULL, full_path, "NULL String Yazma (hicbir sey yapmamali)", 8); // NULL kontrolü


	return 0;
}
