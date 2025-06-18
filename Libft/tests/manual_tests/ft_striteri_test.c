#include <stdio.h>   // For printf
#include <stdlib.h>  // For free (eğer test stringi dinamik tahsis edilmişse)
#include <string.h>  // For strcmp, strlen
#include <ctype.h>   // For tolower, toupper (test helper functions)
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_striteri function prototype (if not in libft.h or commented out)
// void ft_striteri(char *s, void (*f)(unsigned int, char*));

// --- Test için yardımcı callback fonksiyonları ---

// Karakteri büyük harfe dönüştüren callback (yerinde değiştirir)
void to_upper_in_place(unsigned int i, char *c_ptr)
{
    (void)i; // 'i' kullanılmadığı için "unused parameter" uyarısını engellemek için
    if (*c_ptr >= 'a' && *c_ptr <= 'z')
        *c_ptr -= 32; // ASCII farkı 'a'-'A' = 32
}

// Karakteri küçük harfe dönüştüren callback (yerinde değiştirir)
void to_lower_in_place(unsigned int i, char *c_ptr)
{
    (void)i;
    if (*c_ptr >= 'A' && *c_ptr <= 'Z')
        *c_ptr += 32;
}

// Karakterin indeksine göre değiştiren callback
// Çift indeksli karakterleri büyük harfe, tek indekslileri küçük harfe dönüştürür.
void capitalize_even_index_in_place(unsigned int i, char *c_ptr)
{
    if (i % 2 == 0) // Çift indeks
    {
        if (*c_ptr >= 'a' && *c_ptr <= 'z')
            *c_ptr -= 32;
    }
    else // Tek indeks
    {
        if (*c_ptr >= 'A' && *c_ptr <= 'Z')
            *c_ptr += 32;
    }
}

// --- Yardımcı Test Fonksiyonu ---
void test_striteri(char *s, void (*f)(unsigned int, char*), const char *expected_output, const char *description, int test_num)
{
    // Orijinal stringin bir kopyasını alıyoruz ki test sonrası karşılaştırabilelim.
    // Ya da direkt olarak mutable bir string (dizi) kullanabiliriz.
    // Burada test amaçlı, argüman olarak gelen 's'nin değiştirilmesini bekliyoruz.
    char temp_s[100]; // Test stringini tutmak için yeterince büyük bir tampon
    if (s)
        strcpy(temp_s, s); // Kopyasını alıyoruz, çünkü ft_striteri s'yi değiştirecek.
    else
        strcpy(temp_s, ""); // s NULL ise boş string kopyala

    int status = 1; // 1 = PASS, 0 = FAIL

    printf("--- Test %d: %s ---\n", test_num, description);
    printf("  Original string (before call): \"%s\"\n", s ? s : "(NULL)");
    printf("  Expected output:               \"%s\"\n", expected_output ? expected_output : "(NULL)");

    // Kendi ft_striteri fonksiyonumuzu çağırıyoruz
    // Eğer s NULL ise ft_striteri içeride NULL kontrolü yapıp dönecektir, bu yüzden direkt çağırabiliriz.
    ft_striteri(s, f);

    // Sonuçları karşılaştır
    // ft_striteri void döndürdüğü için, s'nin kendisinin değiştiğini kontrol etmeliyiz.
    if (expected_output == NULL) // Eğer beklenen çıktı NULL ise (s veya f NULL ise)
    {
        // Bu durumda ft_striteri hiçbir şey yapmamalı, s orijinal haliyle kalmalı
        // veya NULL ise NULL kalmalı. Testin mantığına bağlı olarak burası değişebilir.
        // Biz burada s'nin NULL olduğu durumları test ediyoruz, bu durumda f çağrılmaz.
        if (s != NULL && f != NULL) { // Eğer girişler geçerliyse ama beklenen NULL ise bu bir hata
            printf("  FAIL: Unexpected NULL expected. This test case might be ill-defined for ft_striteri.\n");
            status = 0;
        } else if (s == NULL && expected_output == NULL) { // s NULL ve beklenen de NULL ise OK
            printf("  Input s was NULL, as expected (no change).\n");
            status = 1; // Passed, as no operation expected
        } else if (f == NULL && expected_output == NULL) { // f NULL ve beklenen de NULL ise OK
            printf("  Input f was NULL, as expected (no operation).\n");
            status = 1; // Passed, as no operation expected
        } else {
            printf("  FAIL: Unexpected NULL scenario. Check test case logic.\n");
            status = 0;
        }
    }
    else // Eğer beklenen çıktı geçerli bir string ise
    {
        if (s == NULL) // s NULL ise ve bir çıktı bekleniyorsa bu bir hatadır
        {
            printf("  FAIL: Input string 's' was NULL, but expected output is non-NULL.\n");
            status = 0;
        }
        else if (f == NULL) // f NULL ise ve bir çıktı bekleniyorsa bu bir hatadır
        {
            printf("  FAIL: Input function 'f' was NULL, but expected output is non-NULL.\n");
            status = 0;
        }
        else if (strcmp(s, expected_output) != 0) // String içerikleri farklıysa
        {
            printf("  FAIL: String content mismatch AFTER ft_striteri call.\n");
            printf("    String after ft_striteri: \"%s\"\n", s);
            status = 0;
        }
        else
        {
            printf("  String content matches AFTER ft_striteri call.\n");
        }
    }

    // Print final status
    printf("  Overall Status: %s\n\n", status ? "GEÇTİ" : "BAŞARISIZ");
}

// --- Ana Fonksiyon ---
int main(void)
{
    printf("--- ft_striteri Testleri ---\n\n");

    // Test 1: Basit büyük harfe dönüştürme
    // DİKKAT: C literal stringler (örn. "hello") değiştirilemezdir.
    // Bu yüzden test için değiştirilebilir char dizileri kullanmalıyız.
    char s1[] = "hello world";
    test_striteri(s1, to_upper_in_place, "HELLO WORLD", "Basit buyuk harfe donusturme", 1);

    // Test 2: Basit küçük harfe dönüştürme
    char s2[] = "HELLO WORLD";
    test_striteri(s2, to_lower_in_place, "hello world", "Basit kucuk harfe donusturme", 2);

    // Test 3: Boş string
    char s3[] = "";
    test_striteri(s3, to_upper_in_place, "", "Bos string", 3);

    // Test 4: Sayılar ve semboller (değişmemeli)
    char s4[] = "123!@#";
    test_striteri(s4, to_upper_in_place, "123!@#", "Sayilar ve semboller", 4);

    // Test 5: İndeks bazlı dönüştürme
    char s5[] = "AbcDeFg";
    test_striteri(s5, capitalize_even_index_in_place, "AbCdEfG", "Indeks bazli donusturme", 5);

    // Test 6: s NULL ise (beklenen: hiçbir şey yapmaması)
    // ft_striteri zaten NULL kontrolü yapıyor. 's' NULL ise NULL olarak kalmalı.
    // Test 's'nin kendisini kontrol edemeyeceği için, beklenen çıktı NULL olarak işaretlenir.
    test_striteri(NULL, to_upper_in_place, NULL, "s NULL", 6);

    // Test 7: f NULL ise (beklenen: hiçbir şey yapmaması)
    char s7[] = "test";
    test_striteri(s7, NULL, NULL, "f NULL", 7); // s7 değişmeden kalmalı

    // Test 8: Sadece bir karakter
    char s8[] = "x";
    test_striteri(s8, to_upper_in_place, "X", "Tek karakter", 8);

    // Test 9: Tüm karakterler trim set içinde olan bir string
    char s9[] = "aaaaa"; // Örnek olarak, eğer callback 'a'ları 'b'ye çevirse
    // Varsayalım ki 'to_upper_in_place' 'a'yı 'A' yapar
    test_striteri(s9, to_upper_in_place, "AAAAA", "Tum karakterler degisir", 9);

    return 0;
}
