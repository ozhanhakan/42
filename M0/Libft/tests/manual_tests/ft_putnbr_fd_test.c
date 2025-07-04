#include <stdio.h>   // For printf (test çıktısı için)
#include <unistd.h>  // For STDOUT_FILENO, STDERR_FILENO, close, open, read
#include <fcntl.h>   // For O_CREAT, O_WRONLY, O_APPEND, O_RDONLY
#include <string.h>  // For strcmp, strlen (doğrulama için)
#include "../../src/libft.h" // Don't forget to include your libft.h here!


#include <fcntl.h> // open fonksiyonu için
#include <unistd.h> // close fonksiyonu için
#include <stdio.h> // printf fonksiyonu için (sadece test çıktısı için)

// libft.h dosyanızda ft_putnbr_fd, ft_putstr_fd, ft_putchar_fd tanımlı olmalı.
// Eğer test dosyasını ayrı derliyorsanız, ft_putnbr_fd'nin prototipini buraya ekleyin:
// void	ft_putnbr_fd(int n, int fd); // Eğer ayrı bir test dosyasıysa ekleyin

void	test_ft_putnbr_fd(void)
{
	int		fd;
	char	*test_file = "txtfiles/putnbr_fd_output.txt";

	// Dosyayı oluştur veya üzerine yaz (O_CREAT | O_WRONLY | O_TRUNC)
	// O_CREAT: Dosya yoksa oluştur
	// O_WRONLY: Sadece yazma modu
	// O_TRUNC: Dosya varsa içeriğini sil
	// 0644: Dosya izinleri (owner: read/write, group/others: read)
	fd = open(test_file,  O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Dosya açılamadı");
		return;
	}

	printf("--- ft_putnbr_fd Testi Başladı ---\n");
	printf("Çıktı '%s' dosyasına yazılıyor.\n", test_file);
	ft_putstr_fd("--------------------------------\n", fd);

	// Pozitif sayılar
	ft_putstr_fd("Test 1: Pozitif Sayı (42)\n", fd);
	ft_putnbr_fd(42, fd);
	ft_putstr_fd("\n--------------------------------\n", fd);

	ft_putstr_fd("Test 2: Büyük Pozitif Sayı (123456789)\n", fd);
	ft_putnbr_fd(123456789, fd);
	ft_putstr_fd("\n--------------------------------\n", fd);

	// Negatif sayılar
	ft_putstr_fd("Test 3: Negatif Sayı (-42)\n", fd);
	ft_putnbr_fd(-42, fd);
	ft_putstr_fd("\n--------------------------------\n", fd);

	ft_putstr_fd("Test 4: Büyük Negatif Sayı (-987654321)\n", fd);
	ft_putnbr_fd(-987654321, fd);
	ft_putstr_fd("\n--------------------------------\n", fd);

	// Sıfır
	ft_putstr_fd("Test 5: Sıfır (0)\n", fd);
	ft_putnbr_fd(0, fd);
	ft_putstr_fd("\n--------------------------------\n", fd);

	// INT_MIN (en küçük int değeri)
	ft_putstr_fd("Test 6: INT_MIN (-2147483648)\n", fd);
	ft_putnbr_fd(-2147483648, fd); // Doğrudan sabit değeri kullanıyoruz
	ft_putstr_fd("\n--------------------------------\n", fd);

	// Birden fazla çağrı
	ft_putstr_fd("Test 7: Ardışık Sayılar (1, -1, 10, -10)\n", fd);
	ft_putnbr_fd(1, fd);
	ft_putstr_fd(", ", fd);
	ft_putnbr_fd(-1, fd);
	ft_putstr_fd(", ", fd);
	ft_putnbr_fd(10, fd);
	ft_putstr_fd(", ", fd);
	ft_putnbr_fd(-10, fd);
	ft_putstr_fd("\n--------------------------------\n", fd);


	// Dosyayı kapat
	close(fd);

	printf("Test tamamlandı. Çıktıyı görmek için '%s' dosyasını kontrol edin.\n", test_file);
	printf("--- ft_putnbr_fd Testi Bitti ---\n");
}

// Ana program (main.c veya benzeri bir dosyada)
/*
int main()
{
    test_ft_putnbr_fd();
    return 0;
}
*/


int main()
{
	test_ft_putnbr_fd();

    // Normal bir sayı
    ft_putstr_fd("Sayı (42): ", 1);
    ft_putnbr_fd(42, 1);
    ft_putchar_fd('\n', 1);

    // Negatif bir sayı
    ft_putstr_fd("Sayı (-123): ", 1);
    ft_putnbr_fd(-123, 1);
    ft_putchar_fd('\n', 1);

    // Sıfır
    ft_putstr_fd("Sayı (0): ", 1);
    ft_putnbr_fd(0, 1);
    ft_putchar_fd('\n', 1);

    // INT_MAX
    ft_putstr_fd("Sayı (INT_MAX): ", 1);
    ft_putnbr_fd(2147483647, 1);
    ft_putchar_fd('\n', 1);

    // INT_MIN (en kritik test)
    ft_putstr_fd("Sayı (INT_MIN): ", 1);
    ft_putnbr_fd(-2147483648, 1);
    ft_putchar_fd('\n', 1);

    return (0);
}