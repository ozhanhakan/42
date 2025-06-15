#include <stdio.h>  // printf için
#include <stdlib.h> // standart atoi için
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

// ft_atoi fonksiyonunun prototipi (eğer libft.h içinde değilse veya yorum satırında bıraktıysan)
// int ft_atoi(const char *nptr);
// Yardımcı test fonksiyonu
void test_atoi(const char *test_str, const char *description, int test_num)
{
    int ft_result;
    int std_result;

    ft_result = ft_atoi(test_str);
    std_result = atoi(test_str);

    printf("Test %d: %s\n", test_num, description);
    printf("  String = \"%s\"\n", test_str);
    printf("  ft_atoi: %d\n", ft_result);
    printf("  atoi:    %d\n", std_result);

    // Özellikle -2147483648 gibi durumlarda, implementasyona bağlı olarak 
    // dönüş değerleri tam olarak aynı sayısal değeri vermese bile (örn. 0),
    // 42'nin beklediği çoğu durumda geçmeli veya aynı davranışı sergilemeli.
    // Bu testte basit eşitlik kontrolü kullanıldı.
    printf("  Durum: %s\n\n", (ft_result == std_result) ? "GEÇTİ" : "BAŞARISIZ");
}

int main(void)
{
    printf("--- ft_atoi Testleri ---\n\n");

    test_atoi("12345", "Basit pozitif sayı", 1);
    test_atoi("-6789", "Basit negatif sayı", 2);
    test_atoi("   \t\n\r\v\f12345", "Baştaki boşluklar", 3);
    test_atoi("+987", "Pozitif işaret", 4);
    test_atoi("   -42", "İşaret ve boşluklar", 5);
    test_atoi("123abc45", "Sayısal olmayan karakterlerle bitiyor", 6);
    test_atoi("xyz123", "Sayısal olmayan karakterlerle başlıyor", 7);
    test_atoi("   \n\t ", "Sadece boşluklar", 8);
    test_atoi("", "Boş string", 9);
    test_atoi("+", "Sadece işaret", 10);
    test_atoi("2147483647", "INT_MAX", 11); // INT_MAX
    test_atoi("-2147483648", "INT_MIN", 12); // INT_MIN
    test_atoi("--123", "Birden fazla işaret", 13);
    test_atoi("+-123", "Birden fazla işaret (karmaşık)", 14);
    test_atoi("-2147483648123", "too long", 15); // INT_MIN
    test_atoi("2147483648123", "too long", 16); // INT_MIN

    return 0;
}
