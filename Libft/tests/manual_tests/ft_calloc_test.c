#include <stdio.h>  // printf için
#include <stdlib.h> // calloc, free için
#include <string.h> // memcmp için
//#include <limits.h> // SIZE_MAX için (ft_calloc içinde kullanılıyorsa)
#include <stdint.h>
#include "../../src/libft.h" // Kendi libft.h dosyanızı buraya dahil etmeyi unutmayın!

// ft_calloc fonksiyonunun prototipi (eğer libft.h içinde değilse veya yorum satırında bıraktıysanız)
// void    *ft_calloc(size_t nmemb, size_t size);
// ft_bzero fonksiyonunun prototipi (eğer libft.h içinde değilse veya yorum satırında bıraktıysanız)
// void    ft_bzero(void *s, size_t n); 

// Yardımcı test fonksiyonu
void test_calloc(size_t nmemb, size_t size, const char *description, int test_num)
{
    void *ft_ptr = NULL;
    void *std_ptr = NULL;
    int status = 1; // 1 = GEÇTİ, 0 = BAŞARISIZ

    printf("Test %d: %s (nmemb=%zu, size=%zu)\n", test_num, description, nmemb, size);

    // Kendi ft_calloc fonksiyonumuzu çağırıyoruz
    ft_ptr = ft_calloc(nmemb, size);
    // Standart calloc fonksiyonunu çağırıyoruz
    std_ptr = calloc(nmemb, size);

    // Bellek tahsisi kontrolü
    if ((ft_ptr == NULL && std_ptr != NULL) || (ft_ptr != NULL && std_ptr == NULL))
    {
        printf("  BAŞARISIZ: Bellek tahsisi durumları farklı.\n");
        status = 0;
    }
    else if (ft_ptr == NULL && std_ptr == NULL)
    {
        printf("  Bellek tahsisi her iki fonksiyonda da BAŞARISIZ oldu (beklenen durum olabilir).\n");
        // Her ikisi de NULL döndürdüyse genellikle geçerli sayılır (örneğin bellek yetersizliği veya overflow)
        // Ancak bu durumda içeriği kontrol edemeyiz.
        if (size != 0 && nmemb > SIZE_MAX / size) // Eğer beklenen bir overflow durumu ise GEÇTİ sayabiliriz
            printf("  Beklenen taşma durumu. Durum: GEÇTİ\n\n");
        else
            printf("  Durum: GEÇTİ (Bellek tahsisi başarısız, ancak tutarlı)\n\n");
        // Her iki pointer da NULL ise, temizlik yapmaya gerek yok.
        return;
    }
    else // Her ikisi de başarılı bir pointer döndürdüyse
    {
        // Boyut sıfır olsa bile, calloc genellikle küçük, geçerli bir pointer döndürebilir
        // ve bu durumda 0 byte'ı sıfırlar (yani aslında hiçbir şey yapmaz).
        // Bu yüzden memcmp'yi ancak total_size > 0 ise kullanmalıyız.
        size_t total_size = nmemb * size;

        if (total_size == 0) {
            printf("  Boyut 0. Bellek tahsisi başarılı ve tutarlı.\n");
        } else {
            // Tahsis edilen belleğin içeriğini karşılaştır (sıfır başlatma kontrolü)
            if (memcmp(ft_ptr, std_ptr, total_size) != 0)
            {
                printf("  BAŞARISIZ: Bellek içerikleri farklı.\n");
                status = 0;
            }
            else
            {
                printf("  Bellek içerikleri doğru şekilde sıfırlanmış ve eşleşiyor.\n");
            }
        }
    }

    // Sonucu yazdır
    printf("  Durum: %s\n\n", status ? "GEÇTİ" : "BAŞARISIZ");

    // Tahsis edilen belleği serbest bırak
    if (ft_ptr)
        free(ft_ptr);
    if (std_ptr)
        free(std_ptr);
}

int main(void)
{
    printf("--- ft_calloc Testleri ---\n\n");

    // Normal tahsisler
    test_calloc(10, 1, "10 byte'lık tek eleman", 1);
    test_calloc(5, 4, "5 adet 4 byte'lık eleman (int boyutu)", 2);
    test_calloc(100, 8, "100 adet 8 byte'lık eleman (long boyutu)", 3);
    test_calloc(1, 1024, "1 adet 1KB eleman", 4);

    // Sıfır değerleri
    test_calloc(0, 10, "0 eleman, 10 byte", 5); // malloc(0) veya calloc(0, X) davranışı platforma bağlı değişebilir
    test_calloc(10, 0, "10 eleman, 0 byte", 6);
    test_calloc(0, 0, "0 eleman, 0 byte", 7);

    // Büyük değerler (potansiyel overflow testleri)
    // Bu testler, SIZE_MAX'e göre sisteminizin bit mimarisine bağlı olarak değişir.
    // Örneğin 64-bit bir sistemde bu değerler taşmayabilir.
    // Lütfen dikkatli kullanın, çok büyük değerler sisteminizi kilitleyebilir.
    test_calloc(SIZE_MAX / 2, 2, "Büyük tahsis (SIZE_MAX / 2 * 2)", 8); // Taşıma riski
    test_calloc(SIZE_MAX / 2 + 1, 2, "Büyük tahsis (Taşma bekleniyor)", 9); // Taşma beklenir
    test_calloc(1, SIZE_MAX, "1 eleman, SIZE_MAX byte", 10); // Taşıma riski
    test_calloc(2, SIZE_MAX / 2 + 1, "2 eleman, SIZE_MAX / 2 + 1 byte (Taşma bekleniyor)", 11); // Taşma beklenir

    // Rastgele boyutlar
    test_calloc(7, 3, "Rastgele küçük boyutlar", 12);

    return 0;
}
