#include <stdio.h> // printf için gerekli
#include <ctype.h> // isalnum (orijinal) fonksiyonu için gerekli
#include "libft.h" // ft_isalnum fonksiyonunuzu içeren libft.h dosyanız

int main() {
    int c;
    int errors = 0; // Hata sayacını başlat

    printf("--- ft_isalnum Testi Başlangıcı ---\n\n");

    // Tekil Karakter Testleri:
    // Bu kısım, her bir karakterin özel durumlarını görmenizi sağlar.
    // 'c' karakterini %c ile yazdırarak daha açıklayıcı hale getirdik.

    // Sayılar
    c = '0';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = '5';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = '9';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");

    // Küçük harfler
    c = 'a';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = 'm';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = 'z';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");

    // Büyük harfler
    c = 'A';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = 'M';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = 'Z';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");

    // Diğer karakterler (alfanümerik olmayan)
    c = ' ';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = '$';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = '@';
    printf("Test '%c': ft_isalnum=%d, isalnum=%d -> Match: %s\n", c, ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = '\n'; // Yeni satır karakteri
    printf("Test '\\n': ft_isalnum=%d, isalnum=%d -> Match: %s\n", ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");
    c = 0; // NULL karakter (ASCII 0)
    printf("Test '\\0': ft_isalnum=%d, isalnum=%d -> Match: %s\n", ft_isalnum(c), isalnum(c),
           (ft_isalnum(c) != 0 && isalnum(c) != 0) ? "YES" :
           (ft_isalnum(c) == 0 && isalnum(c) == 0) ? "YES" : "NO");

    printf("\n--- Kapsamlı ASCII Karakter Testi ---\n");

    // ASCII aralığındaki tüm karakterleri test etme (0-127)
    for (int i = 0; i <= 127; i++) {
        // ft_isalnum'dan beklenen boolean değer
        int ft_result_bool = (ft_isalnum(i) != 0); // 0 değilse true, 0 ise false

        // isalnum'dan beklenen boolean değer
        int original_result_bool = (isalnum(i) != 0); // 0 değilse true, 0 ise false

        // Eğer boolean sonuçlar uyuşmuyorsa, hata var demektir
        if (ft_result_bool != original_result_bool) {
            printf("HATA: Karakter %d ('%c'): ft_isalnum=%d (bool: %d), isalnum=%d (bool: %d)\n",
                   i, i, ft_isalnum(i), ft_result_bool, isalnum(i), original_result_bool);
            errors++;
        }
    }

    // Test özeti
    printf("\n--- Test Özeti ---\n");
    if (errors == 0) {
        printf("Tebrikler! ft_isalnum fonksiyonunuz tüm testleri başarıyla geçti.\n");
    } else {
        printf("Testlerde %d hata bulundu. Lütfen ft_isalnum fonksiyonunuzu gözden geçirin.\n", errors);
    }

    printf("\n--- ft_isalnum Testi Bitti ---\n");

    return 0;
}