# 📝 FT_PRINTF - 42 Okul Projesi

## 🎯 Proje Genel Bakış

**ft_printf**, standart C kütüphanesi fonksiyonu `printf()` özelleştirilmiş bir uygulamasıdır. Bu proje 42 Okul müfredatının bir parçasıdır ve **değişken argüman fonksiyonları**, **format belirleyici ayrıştırma** ve **tür dönüşümü** konularına odaklanır.

### 🔍 printf nedir?

`printf()` biçimlendirilmiş çıktı fonksiyonu olup:
- Yer tutucular (format belirleyiciler) içeren bir format dizesi alır
- Değişken sayıda argümanı kabul eder
- Argümanları belirleyicilere göre dönüştürür ve biçimlendirir
- Biçimlendirilmiş sonucu stdout'a çıkarır

```c
printf("Merhaba %s! %d mesajınız var.\n", "Ahmet", 5);
// Çıktı: Merhaba Ahmet! 5 mesajınız var.
```

---

## 🚀 Desteklenen Format Belirleyiciler

| Belirleyici | Tür | Açıklama | Örnek |
|-------------|-----|----------|-------|
| `%c` | `char` | Tek karakter | `ft_printf("%c", 'A')` → `A` |
| `%s` | `char *` | Dize | `ft_printf("%s", "Merhaba")` → `Merhaba` |
| `%p` | `void *` | İşaretçi adresi | `ft_printf("%p", ptr)` → `0x7fff5fbff8a0` |
| `%d` | `int` | İşaretli ondalık | `ft_printf("%d", -42)` → `-42` |
| `%i` | `int` | İşaretli tam sayı | `ft_printf("%i", 42)` → `42` |
| `%u` | `unsigned int` | İşaretsiz ondalık | `ft_printf("%u", 42U)` → `42` |
| `%x` | `unsigned int` | Küçük harf hex | `ft_printf("%x", 255)` → `ff` |
| `%X` | `unsigned int` | Büyük harf hex | `ft_printf("%X", 255)` → `FF` |
| `%%` | - | Gerçek yüzde işareti | `ft_printf("%%")` → `%` |

---

## 🧠 Değişken Argüman Fonksiyonları Açıklaması

### Değişken Argüman Fonksiyonları Nedir?

Değişken argüman fonksiyonları **değişken sayıda argüman** kabul edebilir. C dilinde bu, `<stdarg.h>` kütüphanesi kullanılarak gerçekleştirilir.

```c
#include <stdarg.h>

// Format dizesi + değişken argümanları kabul eden fonksiyon
int ft_printf(const char *format, ...);
```

### Değişken Argüman Fonksiyonları Nasıl Çalışır

1. **`va_list`** - Argüman bilgilerini tutan tür
2. **`va_start(ap, last_param)`** - Argüman listesini başlat
3. **`va_arg(ap, type)`** - Belirtilen türde sonraki argümanı al
4. **`va_end(ap)`** - Argüman listesini temizle

```c
int ft_printf(const char *format, ...)
{
    va_list args;           // Argüman listesi tanımla
    va_start(args, format); // Son sabit parametre ile başlat
    
    // Format dizesindeki her karakteri işle
    while (*format)
    {
        if (*format == '%')
        {
            format++; // '%' karakterini atla
            
            // Format belirleyiciye göre argüman al
            if (*format == 'd')
            {
                int num = va_arg(args, int);  // int argümanı çıkar
                // num'u dönüştür ve yazdır
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);  // Dizeyi çıkar
                // Dizeyi yazdır
            }
        }
        format++;
    }
    
    va_end(args);  // Temizle
    return (char_count);
}
```

### 🔍 Argüman Yükseltme Kuralları

Argümanlar değişken argüman fonksiyonlarına geçirildiğinde, C otomatik olarak küçük türleri yükseltir:

- `char` → `int`
- `short` → `int`  
- `float` → `double`

```c
// Çağrı: ft_printf("%c", 'A')
// 'A' int'e yükseltilir, bu yüzden int olarak çıkarırız:
int c = va_arg(args, int);  // va_arg(args, char) değil!
```

---

## 🏗️ Proje Yapısı

```
FT_PRINTF/
├── ft_printf.h              # Prototip ve dokümantasyon başlığı
├── ft_printf.c              # Ana printf uygulaması
├── ft_printf_handlers.c     # Format belirleyici işleyici fonksiyonları
├── ft_printf_utils.c        # Yardımcı fonksiyonlar (putchar, itoa, vb.)
├── Makefile                 # Derleme sistemi
├── test_main.c              # Kapsamlı test paketi
└── README.md               # Bu dokümantasyon
```

### 📁 Dosya Açıklamaları

- **`ft_printf.h`** - Fonksiyon prototipleri, include'lar ve değişken argüman fonksiyonları hakkında detaylı dokümantasyon içerir
- **`ft_printf.c`** - Format dizesi ayrıştırma ve argüman çıkarma ile ana printf mantığı
- **`ft_printf_handlers.c`** - Her format belirleyici için ayrı fonksiyonlar (%c, %s, %d, vb.)
- **`ft_printf_utils.c`** - Dize manipülasyonu, sayı dönüşümü ve çıktı için yardımcı fonksiyonlar

---

## 🔧 Kurulum ve Kullanım

### Kütüphaneyi Derle

```bash
# Proje dizinine git
cd ft_printf

# Statik kütüphaneyi derle
make

# Bu, libftprintf.a dosyasını oluşturur
```

### Uygulamayı Test Et

```bash
# Kapsamlı testleri derle ve çalıştır
make test
./test_printf

# Norminette uyumluluğunu kontrol et (42 kodlama standardı)
make norm

# Geçici dosyaları temizle
make clean

# Tam temizlik (kütüphaneyi de kaldırır)
make fclean

# Her şeyi yeniden derle
make re
```

### Projenizde Kullanın

```c
// your_program.c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    // Temel kullanım
    ft_printf("Merhaba Dünya!\n");
    
    // Format belirleyiciler ile
    count = ft_printf("İsim: %s, Yaş: %d, Puan: %.2f%%\n", 
                      "Ahmet", 25, 87.5);
    
    ft_printf("%d karakter yazdırıldı\n", count);
    
    return (0);
}
```

```bash
# Kütüphane ile derle
gcc -Wall -Wextra -Werror your_program.c -L. -lftprintf -o your_program
./your_program
```

---

## 🧪 Test Stratejisi

### Test Kategorileri

1. **Format Belirleyici Testleri** - Her %c, %s, %d, vb.
2. **Sınır Durumları** - NULL işaretçiler, boş dizeler, INT_MIN/MAX
3. **Dönüş Değeri Testleri** - Karakter sayısı doğruluğu
4. **Bellek Testleri** - Sızıntı yok, doğru malloc/free
5. **Performans Testleri** - Birden fazla belirleyici, uzun formatlar

### Örnek Test Çıktısı

```
=== KARAKTER TESTLERİ (%c) ===

Test 1: Tek karakter
ft_printf:  A (döndürülen: 1)
printf:     A (döndürülen: 1)
✓ BAŞARILI

Test 2: NULL dizesi
ft_printf:  (null) (döndürülen: 6)
printf:     (null) (döndürülen: 6)
✓ BAŞARILI
```

---

## 🎓 Öğrenme Hedefleri

Bu projeyi tamamlayarak şunları anlayacaksınız:

### 1. **Değişken Argüman Fonksiyonları**
- `va_list`, `va_start`, `va_arg`, `va_end` nasıl çalışır
- C'de argüman yükseltme kuralları
- Fonksiyon çağrıları için yığın bellek düzeni

### 2. **Format Dizesi Ayrıştırma**
- Durum makinesi kavramları
- Karakter karakter işleme
- Format belirleyici tanıma

### 3. **Tür Dönüşümü**
- Tam sayıdan dizeye dönüşüm (ondalık, onaltılık)
- Bellek adresi biçimlendirme
- İşaretsiz ve işaretli sayı işleme

### 4. **Bellek Yönetimi**
- Sayı dönüşümü için dinamik ayırma
- Bellek sızıntılarını önleme
- Tampon yönetimi

### 5. **Sistem Programlama**
- `write()` sistem çağrısı kullanımı
- Dosya tanımlayıcı kavramları
- Düşük seviye çıktı işlemleri

---

## 🔍 Temel Uygulama Detayları

### Format Ayrıştırma Algoritması

```c
// Basitleştirilmiş ayrıştırma mantığı
while (*format)
{
    if (*format == '%')
    {
        format++;  // '%' karakterini atla
        
        // Format belirleyiciyi ayrıştır
        switch (*format)
        {
            case 'c': count += ft_print_char(va_arg(args, int)); break;
            case 's': count += ft_print_string(va_arg(args, char *)); break;
            case 'd': count += ft_print_decimal(va_arg(args, int)); break;
            // ... diğer belirleyiciler
        }
    }
    else
    {
        // Normal karakter - sadece yazdır
        count += ft_putchar_fd(*format, 1);
    }
    format++;
}
```

### Sayıdan Dizeye Dönüşüm

```c
// Örnek: 42'yi "42"ye dönüştür
char *ft_itoa(int n)
{
    // 1. İşareti işle (negatif sayılar)
    // 2. Gereken basamakları say
    // 3. Dize belleği ayır
    // 4. Sağdan sola dönüştür:
    //    - 42 % 10 = 2 → str[1] = '2'
    //    - 42 / 10 = 4 → 4 % 10 = 4 → str[0] = '4'
    // 5. "42" döndür
}
```

### İşaretçi Adresi Biçimlendirme

```c
// Örnek: 0x7fff5fbff8a0 işaretçisini "0x7fff5fbff8a0"a dönüştür
int ft_print_pointer(void *ptr)
{
    if (!ptr)
        return ft_putstr_fd("(nil)", 1);
    
    count += ft_putstr_fd("0x", 1);  // Önek
    count += ft_itoa_base((unsigned long)ptr, "0123456789abcdef");
    return count;
}
```

---

## 📚 Kaynaklar ve Referanslar

### C Standartları ve Dokümantasyon
- [C11 Standardı - Değişken Argüman Fonksiyonları](https://en.cppreference.com/w/c/variadic)
- [printf() Spesifikasyonu](https://man7.org/linux/man-pages/man3/printf.3.html)
- [stdarg.h Dokümantasyonu](https://en.cppreference.com/w/c/variadic)

### 42 Okul Kaynakları
- [42 Norminette](https://github.com/42School/norminette) - Kodlama standardı denetleyicisi
- [42 Header](https://github.com/42Paris/42header) - Standart dosya başlığı

### Ek Öğrenme
- [Değişken Argüman Fonksiyonlarını Anlama](https://www.cprogramming.com/tutorial/c/lesson17.html)
- [printf Uygulama Eğitimi](https://iq.opengenus.org/how-printf-works-internally/)

---

## 🤝 Katkıda Bulunma

Bu, 42 Okul için eğitim amaçlı bir projedir. Ancak geliştirme önerileri memnuniyetle karşılanır:

1. **Kod İnceleme** - Sınır durumları veya optimizasyonları kontrol edin
2. **Test Durumları** - Daha kapsamlı testler ekleyin
3. **Dokümantasyon** - Açıklamaları geliştirin veya örnekler ekleyin
4. **Performans** - Algoritmik iyileştirmeler önerin

---

## ⚠️ Önemli Notlar

### Sınırlamalar
- Bayrak işleme yok (`-`, `+`, `#`, ` `, `0`)
- Genişlik/hassasiyet belirleyicileri yok
- Uzunluk değiştiricileri yok (`l`, `ll`, `h`, vb.)
- Sadece gerekli format belirleyiciler uygulandı

### Performans Değerlendirmeleri
- Her sayı dönüşümü bellek ayırır - üretim kullanımı için tampon havuzlamayı düşünün
- Birden fazla `write()` çağrısı - dahili tamponlama ile optimize edilebilir
- Özyinelemeli dize oluşturma - yinelemeli yaklaşım daha verimli olabilir

---

## 📄 Lisans

Bu proje 42 Okul müfredatının bir parçasıdır. Kod eğitim amaçlı sağlanmıştır.

---

