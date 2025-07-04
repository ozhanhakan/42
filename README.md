# 42 Projeleri - Piscine ve Libft

## Genel Bakış
Bu depo, 42 okulu müfredatı kapsamında tamamladığım **Piscine** ve **Libft** projelerini içermektedir. Piscine, C programlama diline yoğun bir giriş sunarken, Libft, ilerideki projelerde kullanılabilecek özel bir C kütüphanesi oluşturmayı amaçlar. 

## Projeler

### 1. Piscine
Piscine, C programlama dilinin temel kavramlarını öğretmek için tasarlanmış yoğun bir programlama kampıdır. C programlama becerilerini geliştirmek için çeşitli alıştırmalar içerir.

#### Öne Çıkan Alıştırmalar
- **C00**: Temel çıktı işlevleri (örneğin, `ft_putchar`, `ft_print_alphabet`).
- **C01**: Değişkenler ve işaretçiler (örneğin, `ft_ft`, `ft_swap`).
- **C02–C08**: Dizi manipülasyonu, bellek yönetimi ve dosya işlemleri.
- **Rush**: Konsolda desen çizimi yapan projeler (Rush 00, Rush 01).

### 2. Libft
**Libft**, standart C kütüphanesindeki bazı işlevlerin yeniden yazılmasını ve ek yardımcı işlevlerin geliştirilmesini içeren bir projedir. İlerideki 42 projelerinde kullanılmak üzere temel bir kütüphane olarak tasarlanmıştır.

#### Özellikler
- **Zorunlu Kısım**: `ft_strlen`, `ft_strcpy`, `ft_atoi` gibi işlevlerin yeniden yazılması.
- **Bonus Kısım**: Bağlı liste işlevleri (örneğin, `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`).
- **Ek İşlevler**: Proje gereksinimlerinin ötesinde eklenen yardımcı işlevler (varsa).

#### Dosya Yapısı
```
libft/
├── Makefile
├── libft.h
├── libft.a
├── src/
│   ├── ft_strlen.c
│   ├── ft_strcpy.c
│   ├── ...
└── bonus/
    ├── ft_lstnew.c
    ├── ft_lstadd_front.c
    ├── ...
```

## Kurulum ve Kullanım

### Gereksinimler
- C derleyicisi (örneğin, `gcc`)
- Unix benzeri işletim sistemi (Linux, macOS)
- `make` aracı

### Libft Derleme
1. Libft dizinine gidin:
```bash
cd /yol/libft
```
2. Kütüphaneyi derleyin:
```bash
make
```
   - `libft.a` statik kütüphane dosyasını oluşturur.
   - Bonus işlevleri derlemek için: `make bonus`
   - Nesne dosyalarını temizlemek için: `make clean`
   - Kütüphane ve nesne dosyalarını tamamen silmek için: `make fclean`
   - Yeniden derlemek için: `make re`

### Libft Kullanımı
1. Kendi C projenize kütüphaneyi dahil edin:
```c
#include "libft.h"
```
2. Derleme sırasında kütüphaneyi bağlayın:
```bash
gcc programiniz.c -L. -lft -o programiniz
```

## Notlar
- Sorular veya iş birliği fırsatları için lütfen iletişime geçin.

## İletişim
- **Ad**: Hakan Özhan
- **E-posta**: ozhanhakan@gmail.com

## Lisans
Bu proje, 42 okulu müfredatı kapsamında eğitim amaçlı geliştirilmiştir.